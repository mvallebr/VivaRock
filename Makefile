
all: 
	cd src && make all 


clean: 
	cd src && make clean 

purge:
	cd src && make purge && rm -f vivarock*.stackdump
	
run: all
	cd bin && ./vivarock.exe 
