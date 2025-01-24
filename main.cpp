#include <QCoreApplication>

#include <stdio.h>

#include <jack/jack.h>
#include <jack/midiport.h>

#include <wiringPi.h>

jack_port_t *input_port;
//jack_port_t *output_port;

unsigned char note_OnOff = 0;
unsigned char numeroNota = 0;

/*Definizione dei GPIO della Raspberrry Pi*/
#define GPIO_0    17
#define GPIO_1    18
#define GPIO_2    27
#define GPIO_3    22

void writeGpioData(unsigned char data){

    if(data & 0x01)
        digitalWrite(GPIO_0,HIGH);
    else
        digitalWrite(GPIO_0,LOW);
    if(data & 0x02)
        digitalWrite(GPIO_1,HIGH);
    else
        digitalWrite(GPIO_1,LOW);
    if(data & 0x04)
        digitalWrite(GPIO_2,HIGH);
    else
        digitalWrite(GPIO_2,LOW);
    if(data & 0x08)
        digitalWrite(GPIO_3,HIGH);
    else
        digitalWrite(GPIO_3,LOW);
}
//Funzione che in base alla nota ricevuta imposta i GPIO
void playNote(unsigned char numero_nota, unsigned char note_on_off){

    if(note_on_off == 0){
        writeGpioData(0x00);
        return;
    }
    //INH C B A -> Q3, Q2, Q1, Q0
    //Note Mappate secondo tabella
    int nota = numero_nota % 12;
    switch(nota){
        case 0: //C
            writeGpioData(0x07);
            break;
        case 1://C#
            writeGpioData(0x06);
            break;
        case 2://D
            writeGpioData(0x05);
            break;
        case 3://D#
            writeGpioData(0x04);
            break;
        case 4://E
            writeGpioData(0x03);
            break;
        case 5:://F
            writeGpioData(0x02);
            break;
        case 6://F#
            writeGpioData(0x01);
            break;
        case 7://G
            writeGpioData(0x0F);
            break;
        case 8://G#
            writeGpioData(0x0E);
            break;
        case 9://A
            writeGpioData(0x0D);
            break;
        case 10://A#
            writeGpioData(0x0C);
            break;
        case 11://B
            writeGpioData(0x0B);
            break;
            /*
        case 0x48://Do
            writeGpioData(0x0A);
            break;
            */
    }
}
//Funzione di callback del framework Jack
int process(jack_nframes_t nframes, void *arg)
{
    int i;
    void* port_buf = jack_port_get_buffer(input_port, nframes);

    jack_midi_event_t in_event;
    jack_nframes_t event_index = 0;

    jack_nframes_t event_count = jack_midi_get_event_count(port_buf);
/*
    if(event_count > 1)
    {
        printf(" PB13 controller: have %d events\n", event_count);
        for(i=0; i<event_count; i++)
        {
            jack_midi_event_get(&in_event, port_buf, i);
            printf("    event %d time is %d. 1st byte is 0x%x\n", i, in_event.time, *(in_event.buffer));
        }
    }
 */
    jack_midi_event_get(&in_event, port_buf, 0);

    for(i=0; i<nframes; i++)
    {
        numeroNota = 0;

        if((in_event.time == i) && (event_index < event_count))
        {
            if( ((*(in_event.buffer) & 0xf0)) == 0x90 )//nota on
            {
                /* note on */
                numeroNota = *(in_event.buffer + 1);
                note_OnOff = 1;
            }
            else if( ((*(in_event.buffer)) & 0xf0) == 0x80 )//nota off
            {
                /* note off */
                numeroNota = *(in_event.buffer + 1);
                note_OnOff = 0;
            }
            event_index++;

            if(event_index < event_count)
                jack_midi_event_get(&in_event, port_buf, event_index);
        }
        if(numeroNota != 0){
            playNote(numeroNota,note_OnOff);
        }
    }
    return 0;
}

int srate(jack_nframes_t nframes, void *arg)
{
    printf("the sample rate is now %" PRIu32 "/sec\n", nframes);
    return 0;
}

void jack_shutdown(void *arg)
{
    exit(1);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    printf("Viscount PB13 Controller Started\n");

    // uses BCM numbering of the GPIOs and directly accesses the GPIO registers.
    int ret = wiringPiSetupGpio();

    if(ret == 0)
        printf("wiringPi library opened \n");
    else
        printf("wiringPi library Error %i\n",ret);

    // pin mode ..(INPUT, OUTPUT, PWM_OUTPUT, GPIO_CLOCK)
    pinMode(GPIO_0, OUTPUT);//GPIO0
    pinMode(GPIO_1, OUTPUT);//GPIO1
    pinMode(GPIO_2, OUTPUT);//GPIO2
    pinMode(GPIO_3, OUTPUT);//GPIO3

    writeGpioData(0x00);

    //uint8_t mask = 0x01;
    //while(1){
    //    writeGpioData(mask);
    //    mask = mask << 1;
    //}

    //JackServer initilize
    jack_client_t *client;

    client = jack_client_open ("Viscount PB13", JackNullOption, NULL);

    if (client == 0)
    {
        printf("jack server not running?\n");
        return 1;
    }

    //Jack server callback register
    jack_set_process_callback (client, process, 0);

    jack_on_shutdown (client, jack_shutdown, 0);

    //Create JackServer In and out port
    input_port  = jack_port_register (client, "midi_in",   JACK_DEFAULT_MIDI_TYPE,  JackPortIsInput,  0);

    //Jack server activate
    if (jack_activate (client))
    {
        printf("cannot activate client");
        return 1;
    }

    printf("Main loop started");

    return a.exec();
}
