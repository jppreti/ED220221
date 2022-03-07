all: clear pointers

pointers:
	@echo -e "\nCompilando ponteiros"
	gcc pointers.c -o pointers
	@echo -e "\nhabilitando execução"
	chmod +x pointers

clear:
	@echo -e "\nRemovendo arquivos objeto"
	rm -f pointers