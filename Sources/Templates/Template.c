#include "Templates/Template.h"
#include "General/List.h"
#include <malloc.h>
#include <assert.h>

void Template_AddMinuitia(Template *template, TemplateMinutia *minutia)
{
    List_AddData(&(template->minutiae), minutia);
}

List *Template_GetMinutiae(Template *template)
{
    return &template->minutiae;
}

Template Template_Constuct()
{
    Template template;
    template.minutiae = List_Construct();
    return template;
}

void Template_Free(Template *template)
{
    while (List_GetCount(&(template->minutiae)) > 0)
    {
        void *dataFound;
        List_Remove(&(template->minutiae), (template->minutiae.tail), &dataFound);
        free(dataFound);
    }
}
