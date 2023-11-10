#pragma once

namespace CLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>

	///////////////////////////////////////////
	ref struct MyStruct
	{
		MyStruct(String^ number, String^ year,String^ mark)
		{
			Number = number;
			Year = year;
			Mark = mark;
		}
		System::String^ Number;
		System::String^ Year;
		System::String^ Mark;
	};
	///////////////////////////////////////////



	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::DateTimePicker^  dateTimePicker1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private: array<Control^>^ Objects = gcnew array<Control^>(3);

	private: array<String^>^ FileNames = gcnew array<String^>(GetSize("FileNames.txt"));
	private: array<String^>^ FileNamesRu = gcnew array<String^>(GetSize("FileNamesRu.txt"));
	private: array<String^>^ BuferFileNamesRu = gcnew array<String^>(GetSize("FileNamesRu.txt"));
	//private: array<String^, 2>^ NumberAuto = gcnew array<String^, 2>(GetSize("NumberAuto.txt"), 2);
	private: array<MyStruct^>^ NumberAuto = gcnew array<MyStruct^>(GetSize("NumberAuto.txt"));
	private: array<String^>^ BuferNumberAuto = gcnew array<String^>(GetSize("NumberAuto.txt"));
	private: bool b;

			
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(15, 108);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Сохранить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(72, 22);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(200, 21);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::ComboBox1_TextChanged);
			this->comboBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::ComboBox1_KeyDown);
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(72, 47);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(200, 21);
			this->comboBox2->TabIndex = 2;
			this->comboBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::ComboBox2_TextChanged);
			this->comboBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::ComboBox2_KeyDown);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(72, 74);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(121, 20);
			this->dateTimePicker1->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Шаблон";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 50);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(58, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Номер ТС";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(99, 108);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(94, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Сгенерировать";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(199, 112);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 8;
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 143);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::OnLoad);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ComboBox1_TextChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ComboBox2_TextChanged(System::Object^  sender, EventArgs^  e);
	private: System::Void ComboBox1_KeyDown(System::Object^  sender, KeyEventArgs^  e);
	private: System::Void ComboBox2_KeyDown(System::Object^  sender, KeyEventArgs^  e);
	private: System::Void MyForm_KeyDown(System::Object^  sender, KeyEventArgs^  e);
	private: System::Void OnLoad(System::Object ^sender, System::EventArgs ^e);

	private: void Reader(array<String^>^ arr, System::String^ str);
	private: void Reader(array<MyStruct^>^ arr, System::String^ str);

	private: int GetSize(System::String^ str);
	};
}