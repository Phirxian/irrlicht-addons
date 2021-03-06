/*  GIMP header image file format (RGB): /mnt/windows1/Development/Project/IrrIgesLoader/app/gradient.h  */

static unsigned int width = 15;
static unsigned int height = 151;

/*  Call this macro repeatedly.  After each use, the pixel data can be extracted  */

#define HEADER_PIXEL(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}
static char *header_data =
	"`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!*`Q!4"
	"`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!4`Q!?`Q!?"
	"`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!?`Q!I`Q!I`Q!I"
	"`Q!I`Q!I`Q!I`Q!I`Q!I`Q!I`Q!I`Q!I`Q!I`Q!I`Q!I`Q!I`Q!R`Q!R`Q!R`Q!R"
	"`Q!R`Q!R`Q!R`Q!R`Q!R`Q!R`Q!R`Q!R`Q!R`Q!R`Q!R`Q!\\`Q!\\`Q!\\`Q!\\`Q!\\"
	"`Q!\\`Q!\\`Q!\\`Q!\\`Q!\\`Q!\\`Q!\\`Q!\\`Q!\\`Q!\\`Q\"'`Q\"'`Q\"'`Q\"'`Q\"'`Q\"'"
	"`Q\"'`Q\"'`Q\"'`Q\"'`Q\"'`Q\"'`Q\"'`Q\"'`Q\"'`Q\"1`Q\"1`Q\"1`Q\"1`Q\"1`Q\"1`Q\"1"
	"`Q\"1`Q\"1`Q\"1`Q\"1`Q\"1`Q\"1`Q\"1`Q\"1`Q\";`Q\";`Q\";`Q\";`Q\";`Q\";`Q\";`Q\";"
	"`Q\";`Q\";`Q\";`Q\";`Q\";`Q\";`Q\";`Q\"E`Q\"E`Q\"E`Q\"E`Q\"E`Q\"E`Q\"E`Q\"E`Q\"E"
	"`Q\"E`Q\"E`Q\"E`Q\"E`Q\"E`Q\"E`Q\"O`Q\"O`Q\"O`Q\"O`Q\"O`Q\"O`Q\"O`Q\"O`Q\"O`Q\"O"
	"`Q\"O`Q\"O`Q\"O`Q\"O`Q\"O`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q\"Y"
	"`Q\"Y`Q\"Y`Q\"Y`Q\"Y`Q#\"`Q#\"`Q#\"`Q#\"`Q#\"`Q#\"`Q#\"`Q#\"`Q#\"`Q#\"`Q#\"`Q#\""
	"`Q#\"`Q#\"`Q#\"`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,`Q#,"
	"`Q#,`Q#,`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7`Q#7"
	"`Q#7`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A`Q#A"
	"`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#J`Q#T"
	"`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#T`Q#^`Q#^"
	"`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q#^`Q$)`Q$)`Q$)"
	"`Q$)`Q$)`Q$)`Q$)`Q$)`Q$)`Q$)`Q$)`Q$)`Q$)`Q$)`Q$)`Q$3`Q$3`Q$3`Q$3"
	"`Q$3`Q$3`Q$3`Q$3`Q$3`Q$3`Q$3`Q$3`Q$3`Q$3`Q$3`Q$=`Q$=`Q$=`Q$=`Q$="
	"`Q$=`Q$=`Q$=`Q$=`Q$=`Q$=`Q$=`Q$=`Q$=`Q$=`Q$G`Q$G`Q$G`Q$G`Q$G`Q$G"
	"`Q$G`Q$G`Q$G`Q$G`Q$G`Q$G`Q$G`Q$G`Q$G`Q$P`Q$P`Q$P`Q$P`Q$P`Q$P`Q$P"
	"`Q$P`Q$P`Q$P`Q$P`Q$P`Q$P`Q$P`Q$P`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z"
	"`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z`Q$Z_1$`_1$`_1$`_1$`_1$`_1$`_1$`_1$`_1$`"
	"_1$`_1$`_1$`_1$`_1$`_1$`\\Q$`\\Q$`\\Q$`\\Q$`\\Q$`\\Q$`\\Q$`\\Q$`\\Q$`\\Q$`"
	"\\Q$`\\Q$`\\Q$`\\Q$`\\Q$`ZA$`ZA$`ZA$`ZA$`ZA$`ZA$`ZA$`ZA$`ZA$`ZA$`ZA$`"
	"ZA$`ZA$`ZA$`ZA$`X!$`X!$`X!$`X!$`X!$`X!$`X!$`X!$`X!$`X!$`X!$`X!$`"
	"X!$`X!$`X!$`UA$`UA$`UA$`UA$`UA$`UA$`UA$`UA$`UA$`UA$`UA$`UA$`UA$`"
	"UA$`UA$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`S!$`"
	"S!$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`P1$`"
	"MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`MQ$`K1$`"
	"K1$`K1$`K1$`K1$`K1$`K1$`K1$`K1$`K1$`K1$`K1$`K1$`K1$`K1$`HQ$`HQ$`"
	"HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`HQ$`FA$`FA$`FA$`"
	"FA$`FA$`FA$`FA$`FA$`FA$`FA$`FA$`FA$`FA$`FA$`FA$`CQ$`CQ$`CQ$`CQ$`"
	"CQ$`CQ$`CQ$`CQ$`CQ$`CQ$`CQ$`CQ$`CQ$`CQ$`CQ$`A1$`A1$`A1$`A1$`A1$`"
	"A1$`A1$`A1$`A1$`A1$`A1$`A1$`A1$`A1$`A1$`>Q$`>Q$`>Q$`>Q$`>Q$`>Q$`"
	">Q$`>Q$`>Q$`>Q$`>Q$`>Q$`>Q$`>Q$`>Q$`<A$`<A$`<A$`<A$`<A$`<A$`<A$`"
	"<A$`<A$`<A$`<A$`<A$`<A$`<A$`<A$`:!$`:!$`:!$`:!$`:!$`:!$`:!$`:!$`"
	":!$`:!$`:!$`:!$`:!$`:!$`:!$`71$`71$`71$`71$`71$`71$`71$`71$`71$`"
	"71$`71$`71$`71$`71$`71$`5!$`5!$`5!$`5!$`5!$`5!$`5!$`5!$`5!$`5!$`"
	"5!$`5!$`5!$`5!$`5!$`2A$`2A$`2A$`2A$`2A$`2A$`2A$`2A$`2A$`2A$`2A$`"
	"2A$`2A$`2A$`2A$`/Q$`/Q$`/Q$`/Q$`/Q$`/Q$`/Q$`/Q$`/Q$`/Q$`/Q$`/Q$`"
	"/Q$`/Q$`/Q$`-1$`-1$`-1$`-1$`-1$`-1$`-1$`-1$`-1$`-1$`-1$`-1$`-1$`"
	"-1$`-1$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`*Q$`"
	"*Q$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`(A$`"
	"%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`%Q$`#1$`"
	"#1$`#1$`#1$`#1$`#1$`#1$`#1$`#1$`#1$`#1$`#1$`#1$`#1$`#1$`!!$`!!$`"
	"!!$`!!$`!!$`!!$`!!$`!!$`!!$`!!$`!!$`!!$`!!$`!!$`!!$`!!H`!!H`!!H`"
	"!!H`!!H`!!H`!!H`!!H`!!H`!!H`!!H`!!H`!!H`!!H`!!H`!\"0`!\"0`!\"0`!\"0`"
	"!\"0`!\"0`!\"0`!\"0`!\"0`!\"0`!\"0`!\"0`!\"0`!\"0`!\"0`!\"X`!\"X`!\"X`!\"X`!\"X`"
	"!\"X`!\"X`!\"X`!\"X`!\"X`!\"X`!\"X`!\"X`!\"X`!\"X`!#D`!#D`!#D`!#D`!#D`!#D`"
	"!#D`!#D`!#D`!#D`!#D`!#D`!#D`!#D`!#D`!$,`!$,`!$,`!$,`!$,`!$,`!$,`"
	"!$,`!$,`!$,`!$,`!$,`!$,`!$,`!$,`!$T`!$T`!$T`!$T`!$T`!$T`!$T`!$T`"
	"!$T`!$T`!$T`!$T`!$T`!$T`!$T`!%8`!%8`!%8`!%8`!%8`!%8`!%8`!%8`!%8`"
	"!%8`!%8`!%8`!%8`!%8`!%8`!&$`!&$`!&$`!&$`!&$`!&$`!&$`!&$`!&$`!&$`"
	"!&$`!&$`!&$`!&$`!&$`!&H`!&H`!&H`!&H`!&H`!&H`!&H`!&H`!&H`!&H`!&H`"
	"!&H`!&H`!&H`!&H`!'4`!'4`!'4`!'4`!'4`!'4`!'4`!'4`!'4`!'4`!'4`!'4`"
	"!'4`!'4`!'4`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`!'\\`"
	"!'\\`!'\\`!(D`!(D`!(D`!(D`!(D`!(D`!(D`!(D`!(D`!(D`!(D`!(D`!(D`!(D`"
	"!(D`!),`!),`!),`!),`!),`!),`!),`!),`!),`!),`!),`!),`!),`!),`!),`"
	"!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!)T`!*8`"
	"!*8`!*8`!*8`!*8`!*8`!*8`!*8`!*8`!*8`!*8`!*8`!*8`!*8`!*8`!+$`!+$`"
	"!+$`!+$`!+$`!+$`!+$`!+$`!+$`!+$`!+$`!+$`!+$`!+$`!+$`!+L`!+L`!+L`"
	"!+L`!+L`!+L`!+L`!+L`!+L`!+L`!+L`!+L`!+L`!+L`!+L`!,4`!,4`!,4`!,4`"
	"!,4`!,4`!,4`!,4`!,4`!,4`!,4`!,4`!,4`!,4`!,4`!,\\`!,\\`!,\\`!,\\`!,\\`"
	"!,\\`!,\\`!,\\`!,\\`!,\\`!,\\`!,\\`!,\\`!,\\`!,\\`!-@`!-@`!-@`!-@`!-@`!-@`"
	"!-@`!-@`!-@`!-@`!-@`!-@`!-@`!-@`!-@`!.(`!.(`!.(`!.(`!.(`!.(`!.(`"
	"!.(`!.(`!.(`!.(`!.(`!.(`!.(`!.(`!.P`!.P`!.P`!.P`!.P`!.P`!.P`!.P`"
	"!.P`!.P`!.P`!.P`!.P`!.P`!.P`!/<`!/<`!/<`!/<`!/<`!/<`!/<`!/<`!/<`"
	"!/<`!/<`!/<`!/<`!/<`!/<`!/``!/``!/``!/``!/``!/``!/``!/``!/``!/``"
	"!/``!/``!/``!/``!/``!0L`!0L`!0L`!0L`!0L`!0L`!0L`!0L`!0L`!0L`!0L`"
	"!0L`!0L`!0L`!0L`!0`[!0`[!0`[!0`[!0`[!0`[!0`[!0`[!0`[!0`[!0`[!0`["
	"!0`[!0`[!0`[!0`P!0`P!0`P!0`P!0`P!0`P!0`P!0`P!0`P!0`P!0`P!0`P!0`P"
	"!0`P!0`P!0`G!0`G!0`G!0`G!0`G!0`G!0`G!0`G!0`G!0`G!0`G!0`G!0`G!0`G"
	"!0`G!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<!0`<"
	"!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`2!0`("
	"!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0`(!0__!0__"
	"!0__!0__!0__!0__!0__!0__!0__!0__!0__!0__!0__!0__!0__!0_T!0_T!0_T"
	"!0_T!0_T!0_T!0_T!0_T!0_T!0_T!0_T!0_T!0_T!0_T!0_T!0_K!0_K!0_K!0_K"
	"!0_K!0_K!0_K!0_K!0_K!0_K!0_K!0_K!0_K!0_K!0_K!0_A!0_A!0_A!0_A!0_A"
	"!0_A!0_A!0_A!0_A!0_A!0_A!0_A!0_A!0_A!0_A!0_6!0_6!0_6!0_6!0_6!0_6"
	"!0_6!0_6!0_6!0_6!0_6!0_6!0_6!0_6!0_6!0_,!0_,!0_,!0_,!0_,!0_,!0_,"
	"!0_,!0_,!0_,!0_,!0_,!0_,!0_,!0_,!0_#!0_#!0_#!0_#!0_#!0_#!0_#!0_#"
	"!0_#!0_#!0_#!0_#!0_#!0_#!0_#!0^X!0^X!0^X!0^X!0^X!0^X!0^X!0^X!0^X"
	"!0^X!0^X!0^X!0^X!0^X!0^X!0^O!0^O!0^O!0^O!0^O!0^O!0^O!0^O!0^O!0^O"
	"!0^O!0^O!0^O!0^O!0^O!0^E!0^E!0^E!0^E!0^E!0^E!0^E!0^E!0^E!0^E!0^E"
	"!0^E!0^E!0^E!0^E!0^:!0^:!0^:!0^:!0^:!0^:!0^:!0^:!0^:!0^:!0^:!0^:"
	"!0^:!0^:!0^:!0^0!0^0!0^0!0^0!0^0!0^0!0^0!0^0!0^0!0^0!0^0!0^0!0^0"
	"!0^0!0^0!0^&!0^&!0^&!0^&!0^&!0^&!0^&!0^&!0^&!0^&!0^&!0^&!0^&!0^&"
	"!0^&!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\!0]\\"
	"!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]S!0]H"
	"!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]H!0]>!0]>"
	"!0]>!0]>!0]>!0]>!0]>!0]>!0]>!0]>!0]>!0]>!0]>!0]>!0]>!0]4!0]4!0]4"
	"!0]4!0]4!0]4!0]4!0]4!0]4!0]4!0]4!0]4!0]4!0]4!0]4!0]*!0]*!0]*!0]*"
	"!0]*!0]*!0]*!0]*!0]*!0]*!0]*!0]*!0]*!0]*!0]*!0]!!0]!!0]!!0]!!0]!"
	"!0]!!0]!!0]!!0]!!0]!!0]!!0]!!0]!!0]!!0]!#@]!#@]!#@]!#@]!#@]!#@]!"
	"#@]!#@]!#@]!#@]!#@]!#@]!#@]!#@]!#@]!&0]!&0]!&0]!&0]!&0]!&0]!&0]!"
	"&0]!&0]!&0]!&0]!&0]!&0]!&0]!&0]!(P]!(P]!(P]!(P]!(P]!(P]!(P]!(P]!"
	"(P]!(P]!(P]!(P]!(P]!(P]!(P]!*`]!*`]!*`]!*`]!*`]!*`]!*`]!*`]!*`]!"
	"*`]!*`]!*`]!*`]!*`]!*`]!-P]!-P]!-P]!-P]!-P]!-P]!-P]!-P]!-P]!-P]!"
	"-P]!-P]!-P]!-P]!-P]!00]!00]!00]!00]!00]!00]!00]!00]!00]!00]!00]!"
	"00]!00]!00]!00]!2@]!2@]!2@]!2@]!2@]!2@]!2@]!2@]!2@]!2@]!2@]!2@]!"
	"2@]!2@]!2@]!4`]!4`]!4`]!4`]!4`]!4`]!4`]!4`]!4`]!4`]!4`]!4`]!4`]!"
	"4`]!4`]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!7P]!"
	"7P]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!:0]!"
	"<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!<P]!?0]!"
	"?0]!?0]!?0]!?0]!?0]!?0]!?0]!?0]!?0]!?0]!?0]!?0]!?0]!?0]!A@]!A@]!"
	"A@]!A@]!A@]!A@]!A@]!A@]!A@]!A@]!A@]!A@]!A@]!A@]!A@]!C`]!C`]!C`]!"
	"C`]!C`]!C`]!C`]!C`]!C`]!C`]!C`]!C`]!C`]!C`]!C`]!FP]!FP]!FP]!FP]!"
	"FP]!FP]!FP]!FP]!FP]!FP]!FP]!FP]!FP]!FP]!FP]!I0]!I0]!I0]!I0]!I0]!"
	"I0]!I0]!I0]!I0]!I0]!I0]!I0]!I0]!I0]!I0]!KP]!KP]!KP]!KP]!KP]!KP]!"
	"KP]!KP]!KP]!KP]!KP]!KP]!KP]!KP]!KP]!N0]!N0]!N0]!N0]!N0]!N0]!N0]!"
	"N0]!N0]!N0]!N0]!N0]!N0]!N0]!N0]!P@]!P@]!P@]!P@]!P@]!P@]!P@]!P@]!"
	"P@]!P@]!P@]!P@]!P@]!P@]!P@]!S0]!S0]!S0]!S0]!S0]!S0]!S0]!S0]!S0]!"
	"S0]!S0]!S0]!S0]!S0]!S0]!UP]!UP]!UP]!UP]!UP]!UP]!UP]!UP]!UP]!UP]!"
	"UP]!UP]!UP]!UP]!UP]!X0]!X0]!X0]!X0]!X0]!X0]!X0]!X0]!X0]!X0]!X0]!"
	"X0]!X0]!X0]!X0]!Z@]!Z@]!Z@]!Z@]!Z@]!Z@]!Z@]!Z@]!Z@]!Z@]!Z@]!Z@]!"
	"Z@]!Z@]!Z@]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!\\`]!"
	"\\`]!\\`]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!_@]!"
	"_@]!``E!``E!``E!``E!``E!``E!``E!``E!``E!``E!``E!``E!``E!``E!``E!"
	"`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_]!`_5!"
	"`_5!`_5!`_5!`_5!`_5!`_5!`_5!`_5!`_5!`_5!`_5!`_5!`_5!`_5!`^Q!`^Q!"
	"`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^Q!`^)!`^)!`^)!"
	"`^)!`^)!`^)!`^)!`^)!`^)!`^)!`^)!`^)!`^)!`^)!`^)!`]A!`]A!`]A!`]A!"
	"`]A!`]A!`]A!`]A!`]A!`]A!`]A!`]A!`]A!`]A!`]A!`\\U!`\\U!`\\U!`\\U!`\\U!"
	"`\\U!`\\U!`\\U!`\\U!`\\U!`\\U!`\\U!`\\U!`\\U!`\\U!`\\-!`\\-!`\\-!`\\-!`\\-!`\\-!"
	"`\\-!`\\-!`\\-!`\\-!`\\-!`\\-!`\\-!`\\-!`\\-!`[I!`[I!`[I!`[I!`[I!`[I!`[I!"
	"`[I!`[I!`[I!`[I!`[I!`[I!`[I!`[I!`[!!`[!!`[!!`[!!`[!!`[!!`[!!`[!!"
	"`[!!`[!!`[!!`[!!`[!!`[!!`[!!`Z9!`Z9!`Z9!`Z9!`Z9!`Z9!`Z9!`Z9!`Z9!"
	"`Z9!`Z9!`Z9!`Z9!`Z9!`Z9!`YM!`YM!`YM!`YM!`YM!`YM!`YM!`YM!`YM!`YM!"
	"`YM!`YM!`YM!`YM!`YM!`Y%!`Y%!`Y%!`Y%!`Y%!`Y%!`Y%!`Y%!`Y%!`Y%!`Y%!"
	"`Y%!`Y%!`Y%!`Y%!`X=!`X=!`X=!`X=!`X=!`X=!`X=!`X=!`X=!`X=!`X=!`X=!"
	"`X=!`X=!`X=!`WY!`WY!`WY!`WY!`WY!`WY!`WY!`WY!`WY!`WY!`WY!`WY!`WY!"
	"`WY!`WY!`W1!`W1!`W1!`W1!`W1!`W1!`W1!`W1!`W1!`W1!`W1!`W1!`W1!`W1!"
	"`W1!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!`VI!"
	"`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U]!`U5!"
	"`U5!`U5!`U5!`U5!`U5!`U5!`U5!`U5!`U5!`U5!`U5!`U5!`U5!`U5!`TM!`TM!"
	"`TM!`TM!`TM!`TM!`TM!`TM!`TM!`TM!`TM!`TM!`TM!`TM!`TM!`T)!`T)!`T)!"
	"`T)!`T)!`T)!`T)!`T)!`T)!`T)!`T)!`T)!`T)!`T)!`T)!`SA!`SA!`SA!`SA!"
	"`SA!`SA!`SA!`SA!`SA!`SA!`SA!`SA!`SA!`SA!`SA!`RY!`RY!`RY!`RY!`RY!"
	"`RY!`RY!`RY!`RY!`RY!`RY!`RY!`RY!`RY!`RY!`R1!`R1!`R1!`R1!`R1!`R1!"
	"`R1!`R1!`R1!`R1!`R1!`R1!`R1!`R1!`R1!";
