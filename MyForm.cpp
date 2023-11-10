#include "MyForm.h"
#include<string>
#include<Windows.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;

[STAThread]
int main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CLR::MyForm form;
	Application::Run(%form);
	return 0;
}

System::Void CLR::MyForm::Save_Button_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ Mark = gcnew String("");//Строка с маркой автомобиля
	String^NameOfOrg = gcnew String("Lagoona");//Строка с именем организации("Lagoona"- организация по умолчанию)
	int value, IndexNumberAuto = 0;//Переменная value сохраняет позицию названия шаблона в латинице.

	StreamWriter^ pwriter = gcnew StreamWriter("Bufer.txt", false, System::Text::Encoding::Default);//Открытие файла для записи информации.

	for (int i = 0; i < FileNames->Length; i++)//Цикл определяет название шаблона в латинице.
	{
		if (Doc_Template_ComboBox->Text == FileNamesRu[i])
		{
			value = i;
			break;
		}
	}

	for (; IndexNumberAuto < NumberAuto->Length; IndexNumberAuto++)//Цикл проходится по массиву NumberAuto и определяет есть ли в нём указанный ползователем Гос.номер.
	{
		if (NumberAuto[IndexNumberAuto]->Number == Auto_Number_ComboBox->Text)
			break;
	}

	if (Default_Organization->Checked)//Если чекбокс поставлен, организация по умолчанию меняется.
		NameOfOrg = "City";

	if (!(File::Exists("Resources\\" + FileNames[value] + "-" + NumberAuto[IndexNumberAuto]->Mark + "-" + NameOfOrg + ".doc")))//Проверка на наличие шаблона.
	{
		MyForm::Text = "Шаблон не существует";
		pwriter->Close();
		return System::Void();
	}

	pwriter->WriteLine(FileNames[value] + "-" + NumberAuto[IndexNumberAuto]->Mark + "-" + NameOfOrg + ".doc");//Запись имени шаблона в файл.
	pwriter->WriteLine(Auto_Number_ComboBox->Text);//Запись Гос.номера
	pwriter->WriteLine(NumberAuto[IndexNumberAuto]->Year);//запись года выпуска автмобиля

	if (dateTimePicker->Value.Day<10)//Проверка на необходимость нуля перед значением дня и его запись.
		pwriter->WriteLine("0" + dateTimePicker->Value.Day);
	else
		pwriter->WriteLine(dateTimePicker->Value.Day);

	if (dateTimePicker->Value.Month<10)//Проверка на необходимость нуля перед значением месяца и его запись.
		pwriter->WriteLine("0" + dateTimePicker->Value.Month);
	else
		pwriter->WriteLine(dateTimePicker->Value.Month);

	pwriter->WriteLine(dateTimePicker->Value.Year);//Запись текущего года
	pwriter->Close();

	MyForm::Text = "Сохранено";

	return System::Void();
}

System::Void CLR::MyForm::Generate_Button_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	CreateProcess(TEXT("GenerateWord.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);//Запуск программы для генерации документа Word/

	MyForm::Text = "Сгенерировано";

	return System::Void();
}

System::Void CLR::MyForm::Doc_Template_ComboBox_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (b)//Проверка для предотвращения лишних вызовов функции Doc_Template_ComboBox_TextChanged.
	{
		b = false;
		return System::Void();
	}
	Doc_Template_ComboBox->Text = Doc_Template_ComboBox->Text->ToUpper();//Принудительный набор текста в верхнем регистре.
	Doc_Template_ComboBox->Items->Clear();

	int k = 0;

	for (int i = 0; i < FileNamesRu->Length; i++)//Цикл ищет подходяшие под условия поиска названия шаблонов.
	{
		int value = 0;

		for (int j = 0; j<FileNamesRu[i]->Length && j < Doc_Template_ComboBox->Text->Length; j++)
		{
			if (Doc_Template_ComboBox->Text[j] == FileNamesRu[i][j])
				value++;
		}

		if (value == Doc_Template_ComboBox->Text->Length)
		{
			BuferFileNamesRu[k] = FileNamesRu[i];
			k++;
		}
	}

	for (int i = 0; i < k; i++)//Добавляет подходяшие условиям поиска названия шаблонов в список Doc_Template_ComboBox.
	{
		Doc_Template_ComboBox->Items->Add(BuferFileNamesRu[i]);
	}
	Doc_Template_ComboBox->DroppedDown = true;//Выпадающий список остается открытым
	Doc_Template_ComboBox->SelectionStart = Doc_Template_ComboBox->Text->Length;//Переносит курсор в конец текста.

	MyForm::Text = "";

	return System::Void();
}

System::Void CLR::MyForm::Auto_Number_ComboBox_TextChanged(System::Object ^ sender, EventArgs ^ e)
{
	//Данная функция идентична предыдущей за исключением источника информации(вместо названий шаблонов Гос. номера)
	if (b)
	{
		b = false;
		return System::Void();
	}
	Auto_Number_ComboBox->Text = Auto_Number_ComboBox->Text->ToUpper();
	Auto_Number_ComboBox->Items->Clear();

	int k = 0;

	for (int i = 0; i < NumberAuto->Length; i++)
	{
		int value = 0;

		for (int j = 1; j<NumberAuto[i]->Number->Length + 1 && j < Auto_Number_ComboBox->Text->Length + 1; j++)
		{
			if (j < NumberAuto[i]->Number->Length - 1 && Auto_Number_ComboBox->Text[j - 1] == NumberAuto[i]->Number[j])
				value++;
		}

		if (value == Auto_Number_ComboBox->Text->Length)
		{
			BuferNumberAuto[k] = NumberAuto[i]->Number;
			k++;
		}
	}

	for (int i = 0; i < k; i++)
		Auto_Number_ComboBox->Items->Add(BuferNumberAuto[i]);

	Auto_Number_ComboBox->DroppedDown = true;
	Auto_Number_ComboBox->SelectionStart = Auto_Number_ComboBox->Text->Length;

	MyForm::Text = "";

	return System::Void();
}

System::Void CLR::MyForm::Doc_Template_ComboBox_KeyDown(System::Object ^ sender, KeyEventArgs ^ e)
{
	if (e->KeyCode == Keys::F3 && Doc_Template_ComboBox->Items->Count == 1)//При наличии лишь одного варианта в списке нажатие F3 автоматически заполняет ComboBox им.
	{
		Doc_Template_ComboBox->Text = Doc_Template_ComboBox->Items[0]->ToString();
		b = true;//При выполнении данной операции функция Text_Changed ызывается автоматически. Таким образом останавливается ее выполнение в самом начале.
	}

	if (e->KeyCode == Keys::Down | e->KeyCode == Keys::Up)//При нажатии этих клавиш тоже не должна вызываться функция Text_Changed/ 
		b = true;

	return System::Void();
}

System::Void CLR::MyForm::Auto_Number_ComboBox_KeyDown(System::Object ^ sender, KeyEventArgs ^ e)
{
	if (e->KeyCode == Keys::F3 && Auto_Number_ComboBox->Items->Count == 1)
	{
		Auto_Number_ComboBox->Text = Auto_Number_ComboBox->Items[0]->ToString();
		b = true;
	}
	if (e->KeyCode == Keys::Down | e->KeyCode == Keys::Up)
		b = true;

	return System::Void();
}

System::Void CLR::MyForm::MyForm_KeyDown(System::Object ^ sender, KeyEventArgs ^ e)
{
	if (e->KeyCode == Keys::ControlKey)//При нажатии на Ctrl происходит изменение организации.
	{
		Default_Organization->Checked = !(Default_Organization->Checked);
		return System::Void();
	}

	int in = -1;//Переменная обозначает какой из элементов формы сейчас активен

	for (int i = 0; i < Objects->Length; i++)
	{
		if (Objects[i]->Focused)
			in = i;
	}

	if (e->KeyCode == Keys::F1)//При нажатии F1 активируется следующий элемент.
	{
		if (in == 2)
			in = -1;

		if (in == 0 && Objects[in] == Doc_Template_ComboBox)
			Doc_Template_ComboBox->DroppedDown = false;

		Objects[in + 1]->Focus();
	}
	else if (e->KeyCode == Keys::F2)//При нажатии F2 - предыдущий
	{
		if (in == 0 && Objects[in] == Doc_Template_ComboBox)
			Doc_Template_ComboBox->DroppedDown = false;

		if (in == 0 | in == -1)
			in = 3;
		Objects[in - 1]->Focus();
	}

	return System::Void();
}

System::Void CLR::MyForm::OnLoad(System::Object ^ sender, System::EventArgs ^ e)
{
	dateTimePicker->Value = dateTimePicker->Value.AddMonths(-1);//При загрузке формы сразу устанавливается предыдущий месяц.(Акты выпоняются за предыдущий месяц)
	Reader(FileNames, "FileNames.txt");//Чтение из файлов
	Reader(FileNamesRu, "FileNamesRu.txt");
	Reader(NumberAuto, "NumberAuto.txt");
	Reader(NumberAuto, "NumberAuto.txt");
	Objects[0] = Doc_Template_ComboBox;//Инициализация массива Objects
	Objects[1] = Auto_Number_ComboBox;
	Objects[2] = dateTimePicker;

	return System::Void();
}

void CLR::MyForm::Reader(array<String^>^ arr, System::String^ str)//Чтение названий шаблонов
{
	StreamReader^ preader = gcnew StreamReader(str, System::Text::Encoding::Default);
	preader->ReadLine();

	for (int i = 0; i < arr->Length;)
	{
		str = preader->ReadLine();
		if (str != str->Empty)
		{
			arr[i] = str;
			i++;
		}
	}
	preader->Close();
}

void CLR::MyForm::Reader(array<CLR::MyStruct^>^ arr, System::String^ str)//Чтение Гос. номеров вместе с годом выпуска и маркой.
{
	StreamReader^ preader = gcnew StreamReader(str, System::Text::Encoding::Default);
	preader->ReadLine();

	System::String^ Year;
	System::String^ Mark;

	for (int i = 0; i < arr->Length;)
	{
		str = preader->ReadLine();

		if (str == str->Empty)//Пропуск пробелов в файле
			continue;

		if (str[0] == wchar_t::Parse("/"))//Если строка начинается с /, то она сохраняется как марка или год выпуска
		{
			if (str[1] == wchar_t::Parse("2"))//если после знака "/" идет цифра 2, значит это год выпуска.
				Year = str->Substring(1);
			else
				Mark = str->Substring(1);
		}
		else
		{
			arr[i] = gcnew MyStruct(str, Year, Mark);
			i++;
		}
	}
	preader->Close();
}

int CLR::MyForm::GetSize(System::String ^ str)
{
//Первая строка в файле определяет общее кол-во строк.
	StreamReader^ preader = gcnew StreamReader(str, System::Text::Encoding::Default);
	return Int16::Parse(preader->ReadLine());
}

