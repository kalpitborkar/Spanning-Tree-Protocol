#include "bridge.h"

std::string int_to_letter(int i)
{
    if (i == 1)
        return "A";
    if (i == 2)
        return "B";
    if (i == 3)
        return "C";
    if (i == 4)
        return "D";
    if (i == 5)
        return "E";
    if (i == 6)
        return "F";
    if (i == 7)
        return "G";
    if (i == 8)
        return "H";
    if (i == 9)
        return "I";
    if (i == 10)
        return "J";
    if (i == 11)
        return "K";
    if (i == 12)
        return "L";
    if (i == 13)
        return "M";
    if (i == 14)
        return "N";
    if (i == 15)
        return "O";
    if (i == 16)
        return "P";
    if (i == 17)
        return "Q";
    if (i == 18)
        return "R";
    if (i == 19)
        return "S";
    if (i == 20)
        return "T";
    if (i == 21)
        return "U";
    if (i == 22)
        return "V";
    if (i == 23)
        return "W";
    if (i == 24)
        return "X";
    if (i == 25)
        return "Y";
    if (i == 26)
        return "Z";
}

int bridge::is_root_bridge_bool_to_int()
{
    if (this->is_root_bridge == true)
    {
        return 1;
    }
    else
        return 0;
}

bool bridge::receive(configMessage m)
{
    if (this->is_root_bridge) //if the bridge is root bridge
    {
        if (this->root_bridge_id > m.Bi) //identifies root with smaller id (rule 1)
        {
            this->is_root_bridge = false;                             //not a root bridge anymore
            this->distance_from_root_bridge = m.distance_to_root + 1; //updating the distance from root bridge
            this->root_bridge_id = m.Bi;                              //updating the root bridge id
            this->port_status[m.lan] = "RP";                          //updating the port status for the port
            this->root_lan = m.lan;                                   //setting the root lan
            this->sending_bridge_id = m.Bj;

            return true; //updated
        }
        else
            return false; //no updates
    }
    else //if bridge is not root bridge
    {
        if (
            (this->root_bridge_id > m.Bi) || //(rule 1)
            ( (this->distance_from_root_bridge > m.distance_to_root + 1)  && (this->root_bridge_id == m.Bi) ) || // root with equal id but at a shorter distance (rule 2)
            ( (this->sending_bridge_id > m.Bj)  &&  (this->distance_from_root_bridge == m.distance_to_root + 1)  && (this->root_bridge_id == m.Bi) ) || //root id and distance are equal but sending bridge has smaller id (rule 3)
            ( (this->root_lan > m.lan)  &&  (this->sending_bridge_id == m.Bj)  &&  (this->distance_from_root_bridge == m.distance_to_root + 1)  && (this->root_bridge_id == m.Bi) ) //if first 3 rules cannot determine
        )
        {
             std::cout<<"Bi: "<<m.Bi<<" "<<"root_bridge_id: "<<this->root_bridge_id<<std::endl;

            for (int i = 0; i <= 26; i++)
            {
                if (this->connected_ports[i])
                {
                    this->port_status[i] = "DP"; //updating all port status to "DP"
                }
            }

            this->port_status[m.lan] = "RP";                          //updating the port status for the port
            this->distance_from_root_bridge = m.distance_to_root + 1; //updating the distance from root bridge
            this->root_bridge_id = m.Bi;                              //updating the root bridge id
            this->root_lan = m.lan;                                   //setting the root lan
            this->sending_bridge_id = m.Bj;

            return true; //updated
        }

        else if (
            ((m.distance_to_root < this->distance_from_root_bridge) || (m.distance_to_root == this->distance_from_root_bridge && m.Bj < this->bridge_id)) && (this->port_status[m.lan] != "RP") && (this->port_status[m.lan] != "NP")&& (this->root_bridge_id == m.Bi)
)
        {
            this->port_status[m.lan] = "NP";


            return true;
        }

        else
            return false; //no updates
    }
}

void bridge::print_port_status()
{
    std::cout << "B" << std::to_string(bridge_id) << ": ";
    for (int i = 1; i <= 26; i++)
    {
        if (this->connected_ports[i])
        {
            std::cout << int_to_letter(i) << "-" << this->port_status[i] << " ";
        }
    }
    std::cout << std::endl;
}

void print_trace(configMessage m)
{
    std::cout << m.sender_or_receiver << " "
              << m.Bk << " "
              << "("
              << "B" << std::to_string(m.Bi) << "," << m.distance_to_root << ","
              << "B" << std::to_string(m.Bj) << ")" << std::endl;
}

void bridge::update_active_ports()
{
    for (int i = 1; i <= 26; i++)
    {
        if (this->connected_ports[i] && (this->port_status[i] != "NP"))
        {
            this->active_ports.push_back(i);
        }
    }
}
