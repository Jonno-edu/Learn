EMBEDDED_C_OBC_ROOT := ..
include freertos_posix.mk

.PHONY: smoke clean

smoke: freertos_smoke
	./freertos_smoke

freertos_smoke: smoke_queue_task.c
	@$(FREERTOS_KERNEL_CHECK)
	$(CC) $(FREERTOS_CFLAGS) $(FREERTOS_INCLUDES) smoke_queue_task.c $(FREERTOS_KERNEL_SRCS) $(FREERTOS_LDLIBS) -o freertos_smoke

clean:
	rm -f freertos_smoke *.o
