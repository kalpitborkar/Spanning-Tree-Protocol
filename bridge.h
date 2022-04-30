#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <map>

const char sender = 's';
const char receiver = 'r';

class configMessage
{
public:
    int distance_to_root;    //distance between sending bridge and root bridge
    int time;                //time at which the message is sent
    int Bi;                  //ID of the bridge that the sending bridge believes to be the root bridge
    int Bj;                  //ID of the bridge that is sending the message
    int Bk;                  //ID of the bridge at which the event is occuring
    char sender_or_receiver; //as the name suggests
    int lan;

    //constructor
    configMessage(int distance_to_root, int time, int Bi, int Bj, int Bk, char sender_or_receiver, int lan)
    {
        this->distance_to_root = distance_to_root;
        this->time = time;
        this->Bi = Bi;
        this->Bj = Bj;
        this->Bk = Bk;
        this->sender_or_receiver = sender_or_receiver;
        this->lan = lan;
    }
};

class bridge
{
public:
    int bridge_id;                 //id of the bridge
    int root_bridge_id;            //id of the root bridge
    int distance_from_root_bridge; //distance of the bridge from the root bridge
    bool is_root_bridge;           //whether the bridge thinks it is the root bridge or not
    bool connected_ports[27];      //i'th true position indicates that the bridge is connected to the i'th letter LAN
    std::string port_status[27];   //i'th string contains whether the port connected to the i'th letter LAN is RP,DP or NP
    int root_port;                 //number corresponding to the root port (number i corresponds to the i'th letter)
    int sending_bridge_id;
    int root_lan;                  //number corresponding to the root lan of the bridge
    std::vector<int> active_ports; //contains the active ports (RP or DP) connected to this bridge

    //constructor
    bridge(int bridge_id, bool connected_ports[27])
    {
        this->bridge_id = bridge_id;
        this->root_bridge_id = bridge_id;    //initially every bridge thinks that it is the root bridge
        this->is_root_bridge = true;         //initially every bridge thinks that it is the root bridge
        this->distance_from_root_bridge = 0; //initially every bridge thinks that it is the root bridge
        sending_bridge_id = -1;

        for (int i = 0; i <= 26; i++)
        {
            this->connected_ports[i] = connected_ports[i];
        }

        for (int i = 0; i <= 26; i++)
        {
            if (connected_ports[i])
            {
                port_status[i] = "DP"; //initially all ports are DPs
            }
        }
    }

    int is_root_bridge_bool_to_int(); //converts bool to int
    bool receive(configMessage m);    //actions to be taken when a message is received
    void update_active_ports();

    //output functions
    void print_port_status(); //prints "RP", "DP" and "NP" for the different ports attached to this bridge
};

class order_receive_message
{
public:
    bool operator()(configMessage &cm1, configMessage &cm2)
    {
        return (
            (cm1.Bk < cm2.Bk) ||
            (cm1.Bi < cm2.Bi) && (cm1.Bk == cm2.Bk) ||
            (cm1.distance_to_root < cm2.distance_to_root) && (cm1.Bi == cm2.Bi) && (cm1.Bk == cm2.Bk) ||
            (cm1.Bj < cm2.Bj) && (cm1.distance_to_root == cm2.distance_to_root) && (cm1.Bi == cm2.Bi) && (cm1.Bk == cm2.Bk));
    }
};

class order_send_message
{
    public:
    bool operator()(configMessage &cm1, configMessage &cm2)
    {
        return
        (
            (cm1.Bj < cm2.Bj) ||
            (cm1.Bi < cm2.Bi) &&  (cm1.Bj == cm2.Bj) ||
            (cm1.distance_to_root < cm2.distance_to_root) && (cm1.Bi == cm2.Bi) &&  (cm1.Bj == cm2.Bj)
        );
    }
};

void print_trace(configMessage m); //print the trace
std::string int_to_letter(int i);  //returns i'th letter of the alphabet (a=1, b=2 and so on)
                                   //int letter_to_int(char c); //returns int i corresponding to the i'th letter of the alphabet (a=1,b=2 and so on)
                                   // bool order_receive_message(); //sorting messages in order for receiving
                                   // bool order_send_message(); //sorting messages in order for sending