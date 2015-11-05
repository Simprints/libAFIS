#include "Templates/Template.h"

void AddMinitia(Template *template, Minutia *minutia)
{
    List_AddData(&template->minutiae, minutia);
}