#include "EV_VkClassContainer.h"

namespace EV
{
    std::string EV_VkClassContainer::GetDataType()
    {
        return DataType;
    }

    EV_VkClassContainer::EV_VkClassContainer(EV_App* app, std::string dataType) : 
    App(app), DataType(dataType)
    {
        App->GetVkClasses()->insert(std::pair<std::string, EV_VkClassContainer*>(DataType, this));
    }
}