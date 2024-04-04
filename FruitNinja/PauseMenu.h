#pragma once

namespace FruitNinja {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для PauseMenu
	/// </summary>
	public ref class PauseMenu : public System::Windows::Forms::Form
	{
	public:
		PauseMenu(String^ menuName, String^ buttonOk)
		{
			InitializeComponent();

			lblMenuName->Text = menuName;
			btnContinue->Text = buttonOk;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~PauseMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnContinue;
	protected:
	private: System::Windows::Forms::Button^ btnExit;
	private: System::Windows::Forms::Label^ lblMenuName;


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
			this->btnContinue = (gcnew System::Windows::Forms::Button());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->lblMenuName = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// btnContinue
			// 
			this->btnContinue->BackColor = System::Drawing::Color::DarkRed;
			this->btnContinue->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnContinue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnContinue->Location = System::Drawing::Point(12, 84);
			this->btnContinue->Name = L"btnContinue";
			this->btnContinue->Size = System::Drawing::Size(159, 52);
			this->btnContinue->TabIndex = 0;
			this->btnContinue->Text = L"Продолжить";
			this->btnContinue->UseVisualStyleBackColor = false;
			this->btnContinue->Click += gcnew System::EventHandler(this, &PauseMenu::btnContinue_Click);
			// 
			// btnExit
			// 
			this->btnExit->BackColor = System::Drawing::Color::DarkRed;
			this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnExit->Location = System::Drawing::Point(12, 152);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(159, 52);
			this->btnExit->TabIndex = 0;
			this->btnExit->Text = L"Выйти";
			this->btnExit->UseVisualStyleBackColor = false;
			this->btnExit->Click += gcnew System::EventHandler(this, &PauseMenu::btnExit_Click);
			// 
			// lblMenuName
			// 
			this->lblMenuName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblMenuName->ForeColor = System::Drawing::Color::Navy;
			this->lblMenuName->Location = System::Drawing::Point(12, 9);
			this->lblMenuName->MaximumSize = System::Drawing::Size(160, 75);
			this->lblMenuName->Name = L"lblMenuName";
			this->lblMenuName->Size = System::Drawing::Size(160, 75);
			this->lblMenuName->TabIndex = 1;
			this->lblMenuName->Text = L"Пауза";
			this->lblMenuName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PauseMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Olive;
			this->ClientSize = System::Drawing::Size(182, 230);
			this->Controls->Add(this->lblMenuName);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->btnContinue);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"PauseMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"PauseMenu";
			this->TopMost = true;
			this->ResumeLayout(false);

		}
#pragma endregion
		System::Void btnContinue_Click(System::Object^ sender, System::EventArgs^ e) {
			DialogResult = Windows::Forms::DialogResult::OK;
		}

		System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e) {
			DialogResult = Windows::Forms::DialogResult::Abort;
		}
	};
}
