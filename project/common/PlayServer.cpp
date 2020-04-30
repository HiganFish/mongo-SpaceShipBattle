//
// Created by lsmg on 4/21/20.
//

#include <InetAddress.h>
#include <protobuf/ProtobufServer.h>
#include <EventLoop.h>
#include <Logger.h>
#include "PlayerMoveData.pb.h"
#include "SpawnEnemyData.pb.h"

mongo::net::ProtobufServer* server_internal;

const static int PlayerNumPerRoom = 5;

struct GameRoom
{
    int player_nums = 0;
    mongo::net::TcpConnectionPtr players[PlayerNumPerRoom];
};

typedef std::map<int, GameRoom> DeskToConnMap;
DeskToConnMap conn_map;

typedef std::map<std::string, int> ConnToDeskMap;
ConnToDeskMap desk_map;

int current_room_id = 0;
int current_room_player_num = 0;

void OnPlayMessage(const mongo::net::TcpConnectionPtr& conn, const mongo::net::MessagePtr& message)
{
    std::shared_ptr<mongo::PlayerMoveData> input = std::static_pointer_cast<mongo::PlayerMoveData>(message);

    if (input == nullptr)
    {
        LOG_ERROR << conn->GetConnectionName() << " Invalid Message";
        return;
    }

    int roomid = desk_map[conn->GetConnectionName()];
    GameRoom* room =  &conn_map[roomid];

    LOG_INFO << input->ByteSizeLong() << " " << conn->GetConnectionName() << " OnPlayMessage " << input->timestamp();

    for (int i = 0; i < room->player_nums; ++i)
    {
        server_internal->Send((room->players[i]), message.get());
    }
}

void OnSpawnMessage(const mongo::net::TcpConnectionPtr& conn, const mongo::net::MessagePtr& message)
{
    std::shared_ptr<mongo::SpawnEnemyData> input = std::static_pointer_cast<mongo::SpawnEnemyData>(message);

    if (input == nullptr)
    {
        LOG_ERROR << conn->GetConnectionName() << " Invalid Message";
        return;
    }

    int roomid = desk_map[conn->GetConnectionName()];
    GameRoom* room =  &conn_map[roomid];

    LOG_INFO << input->ByteSizeLong() << " " << conn->GetConnectionName() << " OnSpawnMessage " << input->timestamp();

    for (int i = 0; i < room->player_nums; ++i)
    {
        server_internal->Send((room->players[i]), message.get());
    }
}

void OnCloseCallback(const mongo::net::TcpConnectionPtr& conn)
{

}

void OnNewConnection(const mongo::net::TcpConnectionPtr& conn)
{
    if (current_room_player_num == PlayerNumPerRoom)
    {
        current_room_id++;
        current_room_player_num = 0;
    }
    desk_map[conn->GetConnectionName()] = current_room_id;

    conn_map[current_room_id].player_nums++;
    conn_map[current_room_id].players[current_room_player_num++] = conn;

    LOG_INFO << conn->GetConnectionName() << " roomid: " << current_room_id << " current players: " << current_room_player_num;
}

int main()
{
    mongo::net::EventLoop loop;
    mongo::net::InetAddress addr(8010);
    mongo::net::ProtobufServer server(&loop, "play-server", addr);
    server_internal = &server;

    server.RegistCallback(mongo::PlayerMoveData::descriptor(), OnPlayMessage);
    server.RegistCallback(mongo::SpawnEnemyData::descriptor(), OnSpawnMessage);
    server.SetCloseCallback(OnCloseCallback);
    server.SetNewConnectionCallback(OnNewConnection);

    server.SetThreadNum(2);
    server.Start();
    loop.Loop();
}