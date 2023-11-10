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

System::Void CLR::MyForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ Mark = gcnew String("");
	String^NameOfOrg = gcnew String("AUTO-PARTS");
	int value, IndexNumberAuto = 0;

	StreamWriter^ pwriter = gcnew StreamWriter("Bufer.txt", false, System::Text::Encoding::Default);

	for (int i = 0; i < FileNames->Length; i++)
	{
		if (comboBox1->Text == FileNamesRu[i])
		{
			value = i;
			break;
		}
	}

	for (; IndexNumberAuto < NumberAuto->Length; IndexNumberAuto++)
	{
		if (NumberAuto[IndexNumberAuto]->Number == comboBox2->Text)
			break;
	}

	if (checkBox1->Checked)
		NameOfOrg = "SEDA";

	if (!(File::Exists("Resources\\" + FileNames[value] + "-" + NumberAuto[IndexNumberAuto]->Mark + "-" + NameOfOrg + ".doc")))
	{
		MyForm::Text = "Шаблон не существует";
		pwriter->Close();
		return System::Void();
	}

	pwriter->WriteLine(FileNames[value] + "-" + NumberAuto[IndexNumberAuto]->Mark + "-" + NameOfOrg + ".doc");
	pwriter->WriteLine(comboBox2->Text);
	pwriter->WriteLine(NumberAuto[IndexNumberAuto]->Year);

	if (dateTimePicker1->Value.Day<10)
		pwriter->WriteLine("0" + dateTimePicker1->Value.Day);
	else
		pwriter->WriteLine(dateTimePicker1->Value.Day);

	if (dateTimePicker1->Value.Month<10)
		pwriter->WriteLine("0" + dateTimePicker1->Value.Month);
	else
		pwriter->WriteLine(dateTimePicker1->Value.Month);

	pwriter->WriteLine(dateTimePicker1->Value.Year);
	pwriter->Close();

	MyForm::Text = "Сохранено";

	return System::Void();
}

System::Void CLR::MyForm::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	CreateProcess(TEXT("GenerateWord.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	MyForm::Text = "Сгенерировано";

	return System::Void();
}

System::Void CLR::MyForm::ComboBox1_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (b)
	{
		b = false;
		return System::Void();
	}
	comboBox1->Text = comboBox1->Text->ToUpper();
	comboBox1->Items->Clear();

	int k = 0;

	for (int i = 0; i < FileNamesRu->Length; i++)
	{
		int value = 0;

		for (int j = 0; j<FileNamesRu[i]->Length && j < comboBox1->Text->Length; j++)
		{
			if (comboBox1->Text[j] == FileNamesRu[i][j])
				value++;
		}

		if (value == comboBox1->Text->Length)
		{
			BuferFileNamesRu[k] = FileNamesRu[i];
			k++;
		}
	}

	for (int i = 0; i < k; i++)
	{
		comboBox1->Items->Add(BuferFileNamesRu[i]);
	}
	comboBox1->DroppedDown = true;
	comboBox1->SelectionStart = comboBox1->Text->Length;

	MyForm::Text = "";

	return System::Void();
}

System::Void CLR::MyForm::ComboBox2_TextChanged(System::Object ^ sender, EventArgs ^ e)
{
	if (b)
	{
		b = false;
		return System::Void();
	}
	comboBox2->Text = comboBox2->Text->ToUpper();
	comboBox2->Items->Clear();

	int k = 0;

	for (int i = 0; i < NumberAuto->Length; i++)
	{
		int value = 0;

		for (int j = 1; j<NumberAuto[i]->Number->Length + 1 && j < comboBox2->Text->Length + 1; j++)
		{
			if (j < NumberAuto[i]->Number->Length - 1 && comboBox2->Text[j - 1] == NumberAuto[i]->Number[j])
				value++;
		}

		if (value == comboBox2->Text->Length)
		{
			BuferNumberAuto[k] = NumberAuto[i]->Number;
			k++;
		}
	}

	for (int i = 0; i < k; i++)
		comboBox2->Items->Add(BuferNumberAuto[i]);

	comboBox2->DroppedDown = true;
	comboBox2->SelectionStart = comboBox2->Text->Length;

	MyForm::Text = "";

	return System::Void();
}

System::Void CLR::MyForm::ComboBox1_KeyDown(System::Object ^ sender, KeyEventArgs ^ e)
{
	if (e->KeyCode == Keys::F3 && comboBox1->Items->Count == 1)
	{
		comboBox1->Text = comboBox1->Items[0]->ToString();
		b = true;
	}

	if (e->KeyCode == Keys::Down | e->KeyCode == Keys::Up)
		b = true;

	return System::Void();
}

System::Void CLR::MyForm::ComboBox2_KeyDown(System::Object ^ sender, KeyEventArgs ^ e)
{

	if (e->KeyCode == Keys::F3 && comboBox2->Items->Count == 1)
	{
		comboBox2->Text = comboBox2->Items[0]->ToString();
		b = true;
	}
	if (e->KeyCode == Keys::Down | e->KeyCode == Keys::Up)
		b = true;

	return System::Void();
}

System::Void CLR::MyForm::MyForm_KeyDown(System::Object ^ sender, KeyEventArgs ^ e)
{
	if (e->KeyCode == Keys::ControlKey)
	{
		checkBox1->Checked = !(checkBox1->Checked);
		return System::Void();
	}

	int in = -1;

	for (int i = 0; i < Objects->Length; i++)
	{
		if (Objects[i]->Focused)
			in = i;
	}

	if (e->KeyCode == Keys::F1)
	{
		if (in == 2)
			in = -1;

		if (in == 0 && Objects[in] == comboBox1)
			comboBox1->DroppedDown = false;

		Objects[in + 1]->Focus();
	}
	else if (e->KeyCode == Keys::F2)
	{
		if (in == 0 && Objects[in] == comboBox1)
			comboBox1->DroppedDown = false;

		if (in == 0 | in == -1)
			in = 3;
		Objects[in - 1]->Focus();
	}

	return System::Void();
}

System::Void CLR::MyForm::OnLoad(System::Object ^ sender, System::EventArgs ^ e)
{
	dateTimePicker1->Value = dateTimePicker1->Value.AddMonths(-1);
	Reader(FileNames, "FileNames.txt");
	Reader(FileNamesRu, "FileNamesRu.txt");
	Reader(NumberAuto, "NumberAuto.txt");
	Reader(NumberAuto, "NumberAuto.txt");
	Objects[0] = comboBox1;
	Objects[1] = comboBox2;
	Objects[2] = dateTimePicker1;

	return System::Void();
}

void CLR::MyForm::Reader(array<String^>^ arr, System::String^ str)
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

void CLR::MyForm::Reader(array<CLR::MyStruct^>^ arr, System::String^ str)
{
	StreamReader^ preader = gcnew StreamReader(str, System::Text::Encoding::Default);
	preader->ReadLine();

	System::String^ Year;
	System::String^ Mark;

	for (int i = 0; i < arr->Length;)
	{
		str = preader->ReadLine();

		if (str == str->Empty)
			continue;

		if (str[0] == wchar_t::Parse("/"))
		{
			if (str[1] == wchar_t::Parse("2"))
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
	StreamReader^ preader = gcnew StreamReader(str, System::Text::Encoding::Default);
	return Int16::Parse(preader->ReadLine());
}

