#include <stdlib.h>
#include <assert.h>

#include "Extraction/Model/Minutia.h"
#include "DotRemover.h"

void DotRemover_Filter(List *minutiae)
{
    for (ListElement *i = minutiae->head, *next = NULL; i != NULL; i = next)
    {
        Minutia *minutia = (Minutia *) i->data;
        assert(minutia != NULL);

        //Get the next element here as i may be freed in List_Remove
        next = i->next;
        if (List_GetCount(Minutia_GetRidges(minutia)) == 0)
        {
             int32_t ret = List_Remove(minutiae, i, NULL);
             assert(ret == 0);
        }
    }
}
