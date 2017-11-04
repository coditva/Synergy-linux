#include <stdio.h>

#include "datatypes.h"
#include "event.h"

void event_emit(enum event_type event_type)
{
    printf("emitted event: %d\n", event_type);
}
