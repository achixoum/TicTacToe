#include "ResourceManager.h"

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager()
{
    //go through the unordered map and delete the surface we created
    for (auto i: images)
    {
        SDL_Surface* temp = i.second;
        SDL_FreeSurface(temp);
    }
}

//create an instance for the resource manager
//we creating it as static because we need to make sure
//that it will be 1 only instance
ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager n_manager;
    return n_manager;
}

SDL_Surface* ResourceManager::GetSurface(char* FileName)
{
    //we will look through our surfaces
    //which is an unordered map and see if a file exists
    //and if the file exist then return the associated surface
    auto search = images.find(FileName);
    if (search != images.end())
        return images[FileName];
    else
    {
        SDL_Surface* surface = IMG_Load(FileName);
        images.insert(std::make_pair(FileName,surface));
        return images[FileName];
    }
}