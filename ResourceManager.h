#ifndef PROJECTS_RESOURCEMANAGER_H
#define PROJECTS_RESOURCEMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>

class ResourceManager
{
protected:
    ResourceManager();
    std::unordered_map<char*, SDL_Surface*> images;
public:
    ~ResourceManager();
    static ResourceManager& GetInstance();
    virtual SDL_Surface* GetSurface(char* FileName);
};


#endif //PROJECTS_RESOURCEMANAGER_H
