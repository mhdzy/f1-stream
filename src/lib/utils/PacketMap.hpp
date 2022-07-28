#include <map>
#include <string>

std::map<int, std::string>
    packet_id_to_string = {
        {0, "Motion"},
        {1, "Session"},
        {2, "LapData"},
        {3, "Event"},
        {4, "Participants"},
        {5, "CarSetups"},
        {6, "CarTelemetry"},
        {7, "CarStatus"},
        {8, "FinalClassification"},
        {9, "LobbyInfo"},
        {10, "CarDamage"},
        {11, "SessionHistory"}};

std::map<int, int>
    packet_size_to_id = {
        {1464, 0},
        {632, 1},
        {972, 2},
        {40, 3},
        {1257, 4},
        {1102, 5},
        {1347, 6},
        {1058, 7},
        {1015, 8},
        {1191, 9},
        {948, 10},
        {1155, 11}};
