#pragma once

#include "PauseMenu.h"
#include "Fruit.h"

namespace FruitNinja {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(int screenSizeX, int screenSizeY)
		{
			InitializeComponent();


			this->screenSizeX = screenSizeX;
			this->screenSizeY = screenSizeY;
			setupSettings();

			pauseMenu = gcnew PauseMenu("Пауза", "Продолжить");
			pauseMenu->Location = Point(screenSizeX/2 - 91, screenSizeY/2 - 115);
			viktoryMenu = gcnew PauseMenu("Победа!", "Начать сначала");
			viktoryMenu->Location = Point(screenSizeX/2 - 91, screenSizeY/2 - 115);
			defeatMenu = gcnew PauseMenu("Вы проиграли!", "Начать сначала");
			defeatMenu->Location = Point(screenSizeX/2 - 91, screenSizeY/2 - 115);

			pbTable->Image = gcnew Bitmap(pbTable->Width, pbTable->Height);
			graphics = Graphics::FromImage(pbTable->Image);

			updatingTableLink = gcnew voidDelegate(this, &MyForm::updatingTable);
			updateLblStrickLink = gcnew voidDelegate(this, &MyForm::updateLblStrick);
			switchLblPauseLink = gcnew voidDelegate(this, &MyForm::switchLblPause);
			gameThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::game));
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
	private: System::Windows::Forms::Label^ lblPause;
	private: System::Windows::Forms::PictureBox^ pbTable;
	private: System::Windows::Forms::Label^ lblStrick;




	protected:

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
			this->lblPause = (gcnew System::Windows::Forms::Label());
			this->pbTable = (gcnew System::Windows::Forms::PictureBox());
			this->lblStrick = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTable))->BeginInit();
			this->SuspendLayout();
			// 
			// lblPause
			// 
			this->lblPause->AutoSize = true;
			this->lblPause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblPause->Location = System::Drawing::Point(507, 9);
			this->lblPause->Name = L"lblPause";
			this->lblPause->Size = System::Drawing::Size(26, 26);
			this->lblPause->TabIndex = 0;
			this->lblPause->Text = L"||";
			this->lblPause->Click += gcnew System::EventHandler(this, &MyForm::lblPause_Click);
			// 
			// pbTable
			// 
			this->pbTable->Location = System::Drawing::Point(0, 0);
			this->pbTable->Name = L"pbTable";
			this->pbTable->Size = System::Drawing::Size(544, 470);
			this->pbTable->TabIndex = 1;
			this->pbTable->TabStop = false;
			this->pbTable->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pbTable_MouseDown);
			this->pbTable->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pbTable_MouseUp);
			// 
			// lblStrick
			// 
			this->lblStrick->AutoSize = true;
			this->lblStrick->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblStrick->Location = System::Drawing::Point(12, 9);
			this->lblStrick->Name = L"lblStrick";
			this->lblStrick->Size = System::Drawing::Size(43, 46);
			this->lblStrick->TabIndex = 2;
			this->lblStrick->Text = L"0";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Sienna;
			this->ClientSize = System::Drawing::Size(545, 473);
			this->Controls->Add(this->lblStrick);
			this->Controls->Add(this->pbTable);
			this->Controls->Add(this->lblPause);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTable))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		int screenSizeX;
		int screenSizeY;
		int strick;
		PauseMenu^ pauseMenu;
		PauseMenu^ viktoryMenu;
		PauseMenu^ defeatMenu;
		Graphics^ graphics;
		Thread^ gameThread;
		bool MousePushed;

	public:

		delegate void voidDelegate();
		voidDelegate^ updatingTableLink;
		voidDelegate^ updateLblStrickLink;
		voidDelegate^ switchLblPauseLink;

	private:
		void setupSettings() {
			strick = 0;
			lblPause->Location = Point(screenSizeX - 26, 0);
			pbTable->Width = screenSizeX;
			pbTable->Height = screenSizeY;
			pbTable->Parent = this;
			lblPause->Parent = pbTable;
			lblStrick->Parent = pbTable;
			MousePushed = false;
		}

		void game() {
			List<PointF>^ mousePoints = gcnew List<PointF>();
			while (strick <= 10) {
				bool striked = false;
				Fruit^ fruit = gcnew Fruit(strick, screenSizeX, screenSizeY);
				do {
					if (MousePushed) {
						int mouseX = Cursor->Position.X;
						int mouseY = Cursor->Position.Y;
						mousePoints->Add(PointF(mouseX, mouseY));
						mouseX = Cursor->Position.X;
						mouseY = Cursor->Position.Y;
						mousePoints->Add(PointF(mouseX, mouseY));
						if (fruit->isStriked(mouseX, mouseY)) {
							strick++;
							Invoke(updateLblStrickLink);
							striked = true;
							break;
						}
						graphics->DrawLines(gcnew Pen(Color::Silver, 5), mousePoints->ToArray());
					}
					else
						mousePoints->Clear();
					graphics->FillClosedCurve(gcnew SolidBrush(fruit->getColor()), fruit->getPoints());
					Invoke(updatingTableLink);
					fruit->move();
				} while (fruit->isOnScreen(screenSizeX, screenSizeY));
				if (!striked)
					break;
			}
			Invoke(switchLblPauseLink);
			if (strick == 11) {
				if (viktoryMenu->ShowDialog() == Windows::Forms::DialogResult::OK) {
					strick = 0;
					Invoke(switchLblPauseLink);
					Invoke(updateLblStrickLink);
					game();
				}
				else
					Application::Exit();
			}
			else {
				if (defeatMenu->ShowDialog() == Windows::Forms::DialogResult::OK) {
					strick = 0;
					Invoke(switchLblPauseLink);
					Invoke(updateLblStrickLink);
					game();
				}
				else
					Application::Exit();
			}
		}

		void updatingTable() { 
			pbTable->Refresh();
			graphics->Clear(Color::Sienna);
		}

		System::Void lblPause_Click(System::Object^ sender, System::EventArgs^ e) {
			gameThread->Suspend();
			if (pauseMenu->ShowDialog() == Windows::Forms::DialogResult::OK)
				gameThread->Resume();
			else {
				gameThread->Resume();
				gameThread->Abort();
				Application::Exit();
			}
		}

		void switchLblPause() { lblPause->Enabled = !lblPause->Enabled; }

		void updateLblStrick() { lblStrick->Text = strick.ToString(); }

	    System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) { gameThread->Start(); }

		System::Void pbTable_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) { MousePushed = true; }
	   
		System::Void pbTable_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) { MousePushed = false; }

};
}
