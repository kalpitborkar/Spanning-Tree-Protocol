#include "bridge.h"

class bridgesim
{
public:
    bool trace;
    std::vector<bridge> all_bridges;
    std::map<int, bridge> bridge_id_to_obj;
    std::map<int, std::vector<int>> lan_to_active_bridges;
    std::map<int, std::vector<int>> lan_bridge_map;
    std::map<int, std::vector<int>> bridge_lan_map;

    bridgesim(int trace, std::map<int, std::vector<int>> lan_bridge_map, std::map<int, std::vector<int>> bridge_lan_map)
    {
        if (trace == 1)
        {
            this->trace = true;
        }
        else
            this->trace = false;

        this->lan_bridge_map = lan_bridge_map;
        this->bridge_lan_map = bridge_lan_map;

        for (auto iterator = bridge_lan_map.begin(); iterator != bridge_lan_map.end(); iterator++)
        {
            bool connected_temp[27];
            for (int i = 0; i <= 26; i++)
            {
                connected_temp[i] = false;
            }

            std::vector<int> lan_temp = iterator->second;
            for (int i = 0; i < lan_temp.size(); i++)
            {
                connected_temp[lan_temp[i]] = true;
            }

            bridge create(iterator->first, connected_temp);
            all_bridges.push_back(create);
        }
    }

    void simulateSTP();
    void print_output();
    void update_network();
};
