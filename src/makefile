# ----  generic SDCC Makefile  -----------------------------------------------

C_SRCS   := $(wildcard *.c)
REL_SRCS := $(wildcard *.rel)
IHXES    := $(C_SRCS:.c=.ihx)
BINS     := $(C_SRCS:.c=.bin)

# ---- keep intermediate .ihx files ------------------------------------------
.SECONDARY: $(IHXES)

# ---- cross-platform clean -----------------------------------------------
ifeq ($(COMSPEC)$(ComSpec),)        # empty on Unix
  RM := rm -f
else
  RM := del /F /Q                   # Windows
endif

.PHONY: all clean

all: $(BINS)

# build %.ihx from %.c --------------------------------------------------------
%.ihx: %.c
	sdcc -mz80 --no-std-crt0 --code-loc 0x0000 --data-loc 0x8000 --std c99 --Werror $<

# build %.bin from %.ihx ------------------------------------------------------
%.bin: %.ihx
	sdobjcopy -I ihex -O binary $< $@

# remove every intermediate / output file listed ------------------------------
clean:
	$(RM) *.asm *.bin *.ihx *.lk *.lst *.map *.noi *.rel *.sym
