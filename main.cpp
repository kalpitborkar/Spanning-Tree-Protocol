#include "bridgesim.h"

int letter_to_int(std::string s)
{
    if (s == "A")
        return 1;
    if (s == "B")
        return 2;
    if (s == "C")
        return 3;
    if (s == "D")
        return 4;
    if (s == "E")
        return 5;
    if (s == "F")
        return 6;
    if (s == "G")
        return 7;
    if (s == "H")
        return 8;
    if (s == "I")
        return 9;
    if (s == "J")
        return 10;
    if (s == "K")
        return 11;
    if (s == "L")
        return 12;
    if (s == "M")
        return 13;
    if (s == "N")
        return 14;
    if (s == "O")
        return 15;
    if (s == "P")
        return 16;
    if (s == "Q")
        return 17;
    if (s == "R")
        return 18;
    if (s == "S")
        return 19;
    if (s == "T")
        return 20;
    if (s == "U")
        return 21;
    if (s == "V")
        return 22;
    if (s == "W")
        return 23;
    if (s == "X")
        return 24;
    if (s == "Y")
        return 25;
    if (s == "Z")
        return 26;
}

int main()
{
    std::string str_trace_flag, str_number_of_bridges;
    std::cin >> str_trace_flag;
    std::cin >> str_number_of_bridges;

    std::vector<bridge> all_bridges;
    std::map<int, std::vector<int>> lan_bridge_map;
    std::map<int, std::vector<int>> bridge_lan_map;

    int trace_flag = atoi(str_trace_flag.c_str());
    int number_of_bridges = atoi(str_number_of_bridges.c_str());

    for (int i = 0; i <= number_of_bridges; i++)
    {
        std::string current_line;
        std::getline(std::cin, current_line);
        for (int j = 4; j < current_line.length(); j += 2)
        {
            bridge_lan_map[i].push_back(letter_to_int(std::string(1, current_line[j])));
            lan_bridge_map[letter_to_int(std::string(1, current_line[j]))].push_back(i);
        }
    }

    for (int i = 0; i < number_of_bridges; i++)
    {
        bool connected_ports[27];
        for (int j = 0; j <= 26; j++)
        {
            connected_ports[j] = false;
        }
        for (int j = 1; j <= 26; j++)
        {
            std::vector<int> lan_temp = bridge_lan_map[i]; //all lans connected to i'th bridge
            for (int k = 0; k < lan_temp.size(); k++)
            {
                connected_ports[lan_temp[k]] = true;
            }
        }

        bridge create = bridge(i, connected_ports);
    }

    bridgesim obj_bridgesim(trace_flag, lan_bridge_map, bridge_lan_map);
    obj_bridgesim.simulateSTP();
    obj_bridgesim.print_output();
    obj_bridgesim.update_network();
}
