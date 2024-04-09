#ifndef Game_
#include<iostream>
#include<string>
#include <fstream>
#include "gamemap.h"
namespace Game
{
    void SaveGame(const std::string& filename,
        int money_count,
        int num_brave,
        float x_pos,
        float y_pos,
        int num_boss,
        int num_die,
        UINT mark_value,
        UINT32 val_time,
        bool showboss,
        float x_pos_boss,
        float y_pos_boss)
  {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << money_count << " "
                << num_brave << " "
                << x_pos << " "
                << y_pos << " "
                << num_boss << " "
                << num_die << " "
                << mark_value << " "
                << val_time << " "
                << showboss << " "
                << x_pos_boss<<" "
                <<y_pos_boss<< " "
                << std::endl;
            file.close();
        }
        else {
            std::cerr << "Unable to save game to file " << filename << std::endl;
        }
    }
        bool LoadGame(const std::string& filename,
            int& money_count,
            int& num_brave,
            float& x_pos,
            float& y_pos,
            int& num_boss,
            int& num_die,
            UINT& mark_value,
            UINT32& val_time,
            bool& showboss,
            float& x_pos_boss,
            float& y_pos_boss
            ) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> money_count
                >> num_brave
                >> x_pos
                >> y_pos
                >> num_boss
                >> num_die
                >> mark_value
                >> val_time
                >>showboss
                >> x_pos_boss
                >> y_pos_boss
                ;
               
            file.close();
            return true;
        }
        else {
            std::cerr << "Unable to load game from file " << filename << std::endl;
            return false;
        }
    }
        void SaveDieThreat(int pos) {
            std::ofstream file("Threat.txt", std::ios::app);  
            if (file.is_open()) {
                file << pos << " ";
                file.close();  
            }
            else {
                std::cerr << "Unable to save game to file " << std::endl;
            }
        }
        void ResetThreatGame() {
            
            std::ofstream file("Threat.txt", std::ios::trunc);
            if (file.is_open()) {
                file.close();  
            }
            else {
                std::cerr << "Unable to reset game data." << std::endl;
            }
        }
        void SaveMap(const std::string& name, const Map& game_map_)
        {

            std::ofstream file(name, std::ios::trunc);  
            if (file.is_open())
            {
             
                file << game_map_.max_x_ << " " << game_map_.max_y_ << "\n";

                for (int i = 0; i < MAX_MAP_Y; i++)
                {
                    for (int j = 0; j < MAX_MAP_X; j++)
                    {
                        file << game_map_.tile[i][j] << " ";
                    }
                    file << "\n";
                }

                file.close();
            }
            else
            {
                std::cerr << "Unable to save map to file " << name << std::endl;
            }
        }
        void LoadMapFromTxt(const std::string& name,Map& game_map_)
        {
            std::ifstream file(name);  
            if (file.is_open())
            {
               
                file >> game_map_.max_x_ >> game_map_.max_y_;

               
                for (int i = 0; i < MAX_MAP_Y; i++)
                {
                    for (int j = 0; j < MAX_MAP_X; j++)
                    {
                        file >> game_map_.tile[i][j];
                    }
                }

                file.close();
            }
            else
            {
                std::cerr << "Unable to open file " << name << " for reading" << std::endl;
            }
        }
}
#endif // !Game_

