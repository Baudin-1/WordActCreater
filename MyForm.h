#pragma once

namespace CLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ref struct MyStruct //Объекты этой структуры будут включать в себя данные о автомобиле. 
	{
		MyStruct(String^ number, String^ year,String^ mark)
		{
			Number = number;
			Year = year;
			Mark = mark;
		}
		System::String^ Number;//Гос. номер
		System::String^ Year;//Год выпуска
		System::String^ Mark;//Марка автомобиля
	};

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
         System::Windows::Forms::Button^  Save_Button;
         System::Windows::Forms::Button^  Generate_Button;
	 System::Windows::Forms::ComboBox^  Doc_Template_ComboBox;
	 System::Windows::Forms::ComboBox^  Auto_Number_ComboBox;
	 System::Windows::Forms::CheckBox^  Default_Organization;
	 System::Windows::Forms::DateTimePicker^  dateTimePicker;
	 System::Windows::Forms::Label^  Doc_Template_Label;
	 System::Windows::Forms::Label^  Auto_Number_Label;

	 array<Control^>^ Objects = gcnew array<Control^>(3);//Массив хранит объекты формы.

	 array<String^>^ FileNames = gcnew array<String^>(GetSize("FileNames.txt"));//Хранит названия шаблонов.
	 array<String^>^ FileNamesRu = gcnew array<String^>(GetSize("FileNamesRu.txt"));//Хранит названия шаблонов на русском.
	 array<String^>^ BuferFileNamesRu = gcnew array<String^>(GetSize("FileNamesRu.txt"));//Необходим для хранения результата поиска
	 array<MyStruct^>^ NumberAuto = gcnew array<MyStruct^>(GetSize("NumberAuto.txt"));//Хранит Гос. номера
	 array<String^>^ BuferNumberAuto = gcnew array<String^>(GetSize("NumberAuto.txt"));
	 bool b;//Определяет необходимость остановки функции Text_changed/
	
	System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->Save_Button = (gcnew System::Windows::Forms::Button());
			this->Doc_Template_ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->Auto_Number_ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->dateTimePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->Doc_Template_Label = (gcnew System::Windows::Forms::Label());
			this->Auto_Number_Label = (gcnew System::Windows::Forms::Label());
			this->Generate_Button = (gcnew System::Windows::Forms::Button());
			this->Default_Organization = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// Save_Button
			// 
			this->Save_Button->Location = System::Drawing::Point(15, 108);
			this->Save_Button->Name = L"Save_Button";
			this->Save_Button->Size = System::Drawing::Size(75, 23);
			this->Save_Button->TabIndex = 0;
			this->Save_Button->Text = L"Сохранить";
			this->Save_Button->UseVisualStyleBackColor = true;
			this->Save_Button->Click += gcnew System::EventHandler(this, &MyForm::Save_Button_Click);
			// 
			// Doc_Template_ComboBox
			// 
			this->Doc_Template_ComboBox->FormattingEnabled = true;
			this->Doc_Template_ComboBox->Location = System::Drawing::Point(72, 22);
			this->Doc_Template_ComboBox->Name = L"Doc_Template_ComboBox";
			this->Doc_Template_ComboBox->Size = System::Drawing::Size(200, 21);
			this->Doc_Template_ComboBox->TabIndex = 1;
			this->Doc_Template_ComboBox->TextChanged += gcnew System::EventHandler(this, &MyForm::Doc_Template_ComboBox_TextChanged);
			this->Doc_Template_ComboBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::Doc_Template_ComboBox_KeyDown);
			// 
			// Auto_Number_ComboBox
			// 
			this->Auto_Number_ComboBox->FormattingEnabled = true;
			this->Auto_Number_ComboBox->Location = System::Drawing::Point(72, 47);
			this->Auto_Number_ComboBox->Name = L"Auto_Number_ComboBox";
			this->Auto_Number_ComboBox->Size = System::Drawing::Size(200, 21);
			this->Auto_Number_ComboBox->TabIndex = 2;
			this->Auto_Number_ComboBox->TextChanged += gcnew System::EventHandler(this, &MyForm::Auto_Number_ComboBox_TextChanged);
			this->Auto_Number_ComboBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::Auto_Number_ComboBox_KeyDown);
			// 
			// dateTimePicker
			// 
			this->dateTimePicker->Location = System::Drawing::Point(72, 74);
			this->dateTimePicker->Name = L"dateTimePicker";
			this->dateTimePicker->Size = System::Drawing::Size(121, 20);
			this->dateTimePicker->TabIndex = 4;
			// 
			// Doc_Template_Label
			// 
			this->Doc_Template_Label->AutoSize = true;
			this->Doc_Template_Label->Location = System::Drawing::Point(12, 22);
			this->Doc_Template_Label->Name = L"Doc_Template_Label";
			this->Doc_Template_Label->Size = System::Drawing::Size(46, 13);
			this->Doc_Template_Label->TabIndex = 5;
			this->Doc_Template_Label->Text = L"Шаблон";
			// 
			// Auto_Number_Label
			// 
			this->Auto_Number_Label->AutoSize = true;
			this->Auto_Number_Label->Location = System::Drawing::Point(12, 50);
			this->Auto_Number_Label->Name = L"Auto_Number_Label";
			this->Auto_Number_Label->Size = System::Drawing::Size(58, 13);
			this->Auto_Number_Label->TabIndex = 6;
			this->Auto_Number_Label->Text = L"Номер ТС";
			// 
			// Generate_Button
			// 
			this->Generate_Button->Location = System::Drawing::Point(99, 108);
			this->Generate_Button->Name = L"Generate_Button";
			this->Generate_Button->Size = System::Drawing::Size(94, 23);
			this->Generate_Button->TabIndex = 7;
			this->Generate_Button->Text = L"Сгенерировать";
			this->Generate_Button->UseVisualStyleBackColor = true;
			this->Generate_Button->Click += gcnew System::EventHandler(this, &MyForm::Generate_Button_Click);
			// 
			// Default_Organization
			// 
			this->Default_Organization->AutoSize = true;
			this->Default_Organization->Location = System::Drawing::Point(199, 112);
			this->Default_Organization->Name = L"Default_Organization";
			this->Default_Organization->Size = System::Drawing::Size(15, 14);
			this->Default_Organization->TabIndex = 8;
			this->Default_Organization->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 143);
			this->Controls->Add(this->Default_Organization);
			this->Controls->Add(this->Generate_Button);
			this->Controls->Add(this->Auto_Number_Label);
			this->Controls->Add(this->Doc_Template_Label);
			this->Controls->Add(this->dateTimePicker);
			this->Controls->Add(this->Auto_Number_ComboBox);
			this->Controls->Add(this->Doc_Template_ComboBox);
			this->Controls->Add(this->Save_Button);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::OnLoad);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
         System::Void Save_Button_Click(System::Object^  sender, System::EventArgs^  e);
	 System::Void Generate_Button_Click(System::Object^  sender, System::EventArgs^  e);
	 System::Void Doc_Template_ComboBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
	 System::Void Auto_Number_ComboBox_TextChanged(System::Object^  sender, EventArgs^  e);
	 System::Void Doc_Template_ComboBox_KeyDown(System::Object^  sender, KeyEventArgs^  e);
	 System::Void Auto_Number_ComboBox_KeyDown(System::Object^  sender, KeyEventArgs^  e);
	 System::Void MyForm_KeyDown(System::Object^  sender, KeyEventArgs^  e);
	 System::Void OnLoad(System::Object ^sender, System::EventArgs ^e);

	 void Reader(array<String^>^ arr, System::String^ str);//Функция считывает данные из файла и сохраняет в массив.
	 void Reader(array<MyStruct^>^ arr, System::String^ str);

	 int GetSize(System::String^ str);//Функция получает кол-во элементов в файле(1-й элемент в файле).
	};
}
