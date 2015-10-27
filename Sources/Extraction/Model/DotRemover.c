#include <stdlib.h>
#include <assert.h>

#include "DotRemover.h"

void DotRemover_Filter(SkeletonBuilder *skeleton)
{
    List *list = SkeletonBuilder_GetMinutiae(skeleton);

    for (ListElement *i = list->head; i != NULL; i = i->next)
    {
        SkeletonBuilderMinutia *minutia = (SkeletonBuilderMinutia *) i->data;
        assert(minutia != NULL);

        if (List_GetCount(SkeletonBuilderMinutia_GetRidges(minutia)) == 0)
        {
            int32_t ret = List_Remove(list, i, NULL);
            assert(ret == 0);

            SkeletonBuilderMinutia_Destruct(minutia);
        }
    }
}
