#include "bridgesim.h"

void bridgesim::simulateSTP()
{
    int time = 0;
    bool did_bridges_update = true;

    while (did_bridges_update)
    {
        std::vector<configMessage> store_message_sent, store_message_received;

        for (int i = 0; i < all_bridges.size(); i++)
        {
            bridge current_bridge = all_bridges[i];
            std::vector<int> lans_connected_to_current_bridge;

            lans_connected_to_current_bridge = bridge_lan_map[current_bridge.bridge_id];

            for (int j = 0; j < lans_connected_to_current_bridge.size(); j++)
            {
                if (current_bridge.port_status[lans_connected_to_current_bridge[j]] == "DP")
                {
                    configMessage sending_msg(current_bridge.distance_from_root_bridge, time, current_bridge.root_bridge_id, current_bridge.bridge_id, current_bridge.bridge_id, 's', lans_connected_to_current_bridge[j]);
                    store_message_sent.push_back(sending_msg);


                    for (int k = 0; k < this->lan_bridge_map[lans_connected_to_current_bridge[j]].size(); k++)
                    {                        
                        int temp_int;
                        for (int s = 0; s < all_bridges.size(); s++)
                        {
                            if (all_bridges[s].bridge_id == lan_bridge_map[lans_connected_to_current_bridge[j]][k])
                            {
                                temp_int = s;
                            }
                        }

                        bridge *temp = &this->all_bridges[temp_int];

                        if (temp->bridge_id != current_bridge.bridge_id)
                        {
                            configMessage receiving_msg(current_bridge.distance_from_root_bridge, time + 1, current_bridge.root_bridge_id, current_bridge.bridge_id, temp->bridge_id, 'r', lans_connected_to_current_bridge[j]);
                            store_message_received.push_back(receiving_msg);
                        }
                    }
                }
            }
        }

        did_bridges_update = false;

        if (this->trace)
        {
            std::sort(store_message_sent.begin(), store_message_sent.end(), order_send_message());
            for (int j = 0; j < store_message_sent.size(); j++)
            {
                print_trace(store_message_sent[j]);
            }

            std::sort(store_message_received.begin(), store_message_received.end(), order_receive_message());
            for (int j = 0; j < store_message_received.size(); j++)
            {
                print_trace(store_message_received[j]);
            }
        }

        //condition for loop
        for (int i = 0; i < store_message_received.size(); i++)
        {
            int int_temp;
            for(int j=0;j<this->all_bridges.size();j++)
            {
                if(this->all_bridges[j].bridge_id == store_message_received[i].Bk)
                {
                    int_temp = j;
                }
            }
            bridge *receiving_bridge = &this->all_bridges[int_temp];
            did_bridges_update = receiving_bridge->receive(store_message_received[i]);
        }

        

        time += 1;
    }
}

void bridgesim::update_network()
{
    for(auto i = this->bridge_id_to_obj.begin();i!=bridge_id_to_obj.end();i++)
    {
        (i->second).update_active_ports();
        for(auto it=(i->second).active_ports.begin();it!=(i->second).active_ports.end();it++)
        {
            this->lan_to_active_bridges[*it].push_back(i->first);
        }
    }
}

void bridgesim::print_output()
{
    for (int i = 0; i < all_bridges.size(); i++)
    {
        if(i==0)
        {
            continue;
        }
        int int_temp;
        for(int j=0;j<all_bridges.size();j++)
        {
            if(i == all_bridges[j].bridge_id)
            {
                int_temp = j;
            }
        }

        all_bridges[int_temp].print_port_status();
    }
}


