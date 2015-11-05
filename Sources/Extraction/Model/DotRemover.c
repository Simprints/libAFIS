#include <stdlib.h>
#include <assert.h>

#include "DotRemover.h"

void DotRemover_Filter(List *minutiae)
{
    for (ListElement *i = minutiae->head; i != NULL; i = i->next)
    {
        SkeletonBuilderMinutia *minutia = (SkeletonBuilderMinutia *) i->data;
        assert(minutia != NULL);

        if (List_GetCount(SkeletonBuilderMinutia_GetRidges(minutia)) == 0)
        {
            int32_t ret = List_Remove(minutiae, i, NULL);
            assert(ret == 0);
        }
    }
}
