all:
	gcc -o proj main.c patient.c region.c date.c utils.c patientUtils.c regionCommands.c patientCommands.c mixedCommands.c topfivestats.c listArrayList.c listElem.c mapElem.c mapSortedArrayList.c -g -lm
clear:
	rm -f proj