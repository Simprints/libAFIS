#include <stdlib.h>
#include <assert.h>

#include "Extraction/Model/Minutia.h"
#include "DotRemover.h"

void DotRemover_Filter(List *minutiae)
{
    for (ListElement *i = minutiae->head; i != NULL; i = i->next)
    {
        Minutia *minutia = (Minutia *) i->data;
        assert(minutia != NULL);

        if (List_GetCount(Minutia_GetRidges(minutia)) == 0)
        {
            int32_t ret = List_Remove(minutiae, i, NULL);
            assert(ret == 0);
        }
    }
}
