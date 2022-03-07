all: clear pointers

pointers:
	@echo -e "\nCompilando ponteiros"
	gcc pointers.c -o pointers
	gcc pointers2.c -o pointers2
	@echo -e "\nhabilitando execução"
	chmod +x pointers
	chmod +x pointers2

clear:
	@echo -e "\nRemovendo arquivos objeto"
	rm -f pointers pointers2