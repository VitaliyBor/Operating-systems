#pragma once 

struct LBlockDescriptor {
	size_t nextFreeBlock;//здвиг
};

struct PageDescriptor {
	size_t next; //список страниц идентичного состояния	
	LBlockDescriptor* firstFree; //свободный блок с состоянием 1
	size_t bsize; // размер lBlock с состоянием 1 или кол-во блоков с состоянием 2
	char state; //0-free, 1-lblock, 2-mblock	
};

class Allocator {
public:
	Allocator(const size_t ms, const size_t ps);

	//вернуть адрес начала блока или NULL
	void* mem_alloc(size_t size);

	//вернуть адрес начала нового блока или NULL
	void* mem_realloc(void *addr, size_t size);

	//освободить блок по адресу
	void mem_free(void *addr);

	//вывести информацию про блок
	void mem_dump();

private:
	size_t* begin;
	size_t* pagesBegin;
	size_t size;
	size_t pages;
	size_t pageSize;
	PageDescriptor* pageDescriptors;
	size_t* lBlocks;

	size_t lBlocksLength;

	size_t firstFreePage;
	//определить тип состояния для необходимого размера
	PageDescriptor defineCategory(size_t s);
	size_t defineBlockSize(size_t s);

	//инициализация пустых страниц
	void initPages();
	// получить свободные блоки нужного размера
	size_t* getFreeLBlock(size_t bs);
	size_t getIndex(size_t s);

	size_t createLBlockPage(size_t bs);
	size_t getFreePage();
	//возвращает адрес страницы по индексу из массива страниц
	size_t* getAbsolutePageAddr(size_t index);
	//освободить все блоки страницы
	void setAllFree(PageDescriptor pd);
	//возвращает большой блок с длинной ps*pageSize
	size_t* getFreeMBlock(size_t ps);
	//Проверить свободен ли последний блок страницы
	bool freeLBlockIsLast(PageDescriptor pd);
	//определить номер страницы по ее адресу
	size_t findPageByAddress(size_t* addr);
	//определить номер блока по его адресу
	size_t findBlockByAddress(size_t* addr, size_t bs);
	//скопировать информацию
	void copyData(size_t* from, size_t* to, size_t length);
};
