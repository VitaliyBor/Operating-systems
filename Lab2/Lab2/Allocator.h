#pragma once 

struct LBlockDescriptor {
	size_t nextFreeBlock;//�����
};

struct PageDescriptor {
	size_t next; //������ ������� ����������� ���������	
	LBlockDescriptor* firstFree; //��������� ���� � ���������� 1
	size_t bsize; // ������ lBlock � ���������� 1 ��� ���-�� ������ � ���������� 2
	char state; //0-free, 1-lblock, 2-mblock	
};

class Allocator {
public:
	Allocator(const size_t ms, const size_t ps);

	//������� ����� ������ ����� ��� NULL
	void* mem_alloc(size_t size);

	//������� ����� ������ ������ ����� ��� NULL
	void* mem_realloc(void *addr, size_t size);

	//���������� ���� �� ������
	void mem_free(void *addr);

	//������� ���������� ��� ����
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
	//���������� ��� ��������� ��� ������������ �������
	PageDescriptor defineCategory(size_t s);
	size_t defineBlockSize(size_t s);

	//������������� ������ �������
	void initPages();
	// �������� ��������� ����� ������� �������
	size_t* getFreeLBlock(size_t bs);
	size_t getIndex(size_t s);

	size_t createLBlockPage(size_t bs);
	size_t getFreePage();
	//���������� ����� �������� �� ������� �� ������� �������
	size_t* getAbsolutePageAddr(size_t index);
	//���������� ��� ����� ��������
	void setAllFree(PageDescriptor pd);
	//���������� ������� ���� � ������� ps*pageSize
	size_t* getFreeMBlock(size_t ps);
	//��������� �������� �� ��������� ���� ��������
	bool freeLBlockIsLast(PageDescriptor pd);
	//���������� ����� �������� �� �� ������
	size_t findPageByAddress(size_t* addr);
	//���������� ����� ����� �� ��� ������
	size_t findBlockByAddress(size_t* addr, size_t bs);
	//����������� ����������
	void copyData(size_t* from, size_t* to, size_t length);
};
