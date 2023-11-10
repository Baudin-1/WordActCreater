#include<fstream>
#include<string>

#define Uses_MSO2007
#import "C:\Program Files\Common Files\Microsoft Shared\Office12\MSO.DLL"
#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#import "D:\MS WORD\Office12\MSWORD.OLB" \
rename("ExitWindows", "_ExitWindows")
#import "C:\Program Files\Common Files\Microsoft Shared\DAO\DAO360.DLL" \
rename("EOF","EndOfFile") rename("BOF","BegOfFile")

using namespace Word;

void Replace(Word::FindPtr &f, std::string str1, std::string str2);//Функция поиска и замены.

int main()
{

	::CoInitialize(NULL);
	{
		std::ifstream in("Bufer.txt");//Забираем данные из файла

		std::string FileName;
		std::string NumberAuto;
		std::string YearAuto;
		std::string Day;
		std::string Month;
		std::string Year;

		in >> FileName;
		in >> NumberAuto;
		in >> YearAuto;
		in >> Day;
		in >> Month;
		in >> Year;

		in.close();

		FileName = "D:\\MY PROJECTS\\wd\\Resources\\" + FileName;

		_ApplicationPtr word(L"Word.Application");
		word->Visible = true;
		word->Activate();

		_DocumentPtr wdoc1 = word->Documents->Open(&_variant_t(FileName.c_str()));//Открываем документ

		Word::FindPtr f = word->Selection->Find;

		Replace(f, "<D>", Day);
		Replace(f, "<M>", Month);
		Replace(f, "<YY>", Year);
		Replace(f, "<NNNN>", NumberAuto);
		Replace(f, "<GG>", YearAuto);

		wdoc1->Range()->Copy();//Копируем содержание получившегося документа

		wdoc1->Close(&_variant_t(Word::WdSaveOptions::wdDoNotSaveChanges));//Закрываем шаблон без сохранения
		word->Quit();
	}
	::CoUninitialize();

	return 0;
}

	void Replace(Word::FindPtr &f, std::string find_text, std::string replacement_text)
	{
		f->ClearFormatting();//Очищаем фильтры поиска и замены
		f->Text = find_text.c_str();//Определяем искомый текст
		f->Replacement->ClearFormatting();
		f->Replacement->Text = replacement_text.c_str();
		f->Execute(&vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &_variant_t(Word::WdReplace::wdReplaceAll), &vtMissing, &vtMissing, &vtMissing, &vtMissing);//Функция замены текста.
	}
