#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Graphics.hpp>

#include "collision_control.hpp"
#include "object_manager.hpp"

class EventManager
{
public:
    EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    void Init( sf::RenderWindow *renderWindow, ObjectManager *objectManager );

    void listen(  );

    inline uint32_t getType() { return _type; };
    inline void setType( uint32_t type ) { _type = type; };

private:
    void keyboardEvent( sf::Event const& event );
    void leftMouseEvent();
    void modifyConnection( Component *component );

private:
    sf::RenderWindow *_renderWindow{ nullptr };
    ObjectManager *_objectManager{ nullptr };

    uint32_t _type{ LIGHT };
};

#endif