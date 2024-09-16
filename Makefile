NAME = rpgos
TARGETS = $(NAME).iso $(NAME).cue
INCLUDE = include
TOOLS = tools
LD = saturn-sh2-ld
GCC = saturn-sh2-gcc
EMU_YABAUSE = yabause -a -nb -i
EMU_MEDNAFEN = mednafen -psx.dbg_level 0 -video.fs 0 -cheats 1
CFLAGS = -Wall -Wextra -nostdinc -nostdlib -fno-builtin -fno-common
LDFLAGS = -Map $(NAME).map -s -x -T $(NAME).ld
OBJS = entry.o main.o

all: $(TARGETS)

$(NAME).cue: $(NAME).iso
	$(TOOLS)/make_cue.sh $< >$@

$(NAME).iso: 0.BIN dummy.txt
	$(TOOLS)/iso9660.sh $^ >$@

0.BIN: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $+

# ISO内に2つ以上のファイルを置くようにする。
# （どういう訳か、内蔵でないBIOSを用いたYabauseではそうでないと動かない。）
dummy.txt:
	echo dummy >$@

%.o: %.s
	$(GCC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

run_yabause: $(NAME).cue
	$(EMU_YABAUSE) $<

run_mednafen: $(NAME).cue
	$(EMU_MEDNAFEN) $<

run: run_yabause

clean:
	rm -f *~ *.o *.map 0.BIN dummy.txt $(TARGETS) $(INCLUDE)/*~ $(TOOLS)/*~ $(TOOLS)/*.o

clean_all:
	rm IP.BIN

.PHONY: run clean
