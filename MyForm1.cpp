#include "MyForm1.h"
using namespace System::Data;
using namespace System::Data::OleDb;

System::Void Project2::MyForm1::button_download_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Database31.mdb";//подключились
	OleDbConnection^ dbConnection= gcnew OleDbConnection(connectionString);

	dbConnection->Open();//открываем соединение
	String^ query = "SELECT * FROM [Database31]";//запрос
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);//команда
	OleDbDataReader^ dbReader = dbComand->ExecuteReader();//считываем
	
	//проверка
	if (dbReader->HasRows == false) {
		MessageBox::Show("Ошибка считывания данных", "Error");
	}
	else {
		while (dbReader->Read()) {
			dataGridView1->Rows->Add(dbReader["ID"], dbReader["Tarif"], dbReader["Price"], dbReader["Discount"]);
		}
	}
	dbReader->Close();
	dbConnection->Close();
	return System::Void();
}

System::Void Project2::MyForm1::button_add_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выберите одну строку для добавления");
		return;
	}int index = dataGridView1->SelectedRows[0]->Index;

	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr) {
		MessageBox::Show("не все данные введены");
		return;
	}
	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();
	String^ Tarif = dataGridView1->Rows[index]->Cells[1]->Value->ToString();
	String^ Price = dataGridView1->Rows[index]->Cells[2]->Value->ToString();
	String^ Discount = dataGridView1->Rows[index]->Cells[3]->Value->ToString();
	String^ connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Database31.mdb";//подключились
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	bool fl = true;
	int kol = 0;
	for each (char ch in id) {
		if (ch < '0' || ch > '9') {
			fl = false;
			break;
		}
		kol += 1;
	}
	if (!fl || String::IsNullOrWhiteSpace(id) || kol > 7) {
		MessageBox::Show("Вы ввели некорректные данные!", "Внимание!");
		return;
	}

	kol = 0;
	fl = true;
	for each (char ch in Price) {
		if (ch < '0' || ch > '9') {
			fl = false;
			break;
		}
		kol += 1;
	}
	if (!fl || String::IsNullOrWhiteSpace(Price) || kol > 7) {
		MessageBox::Show("Вы ввели некорректные данные!", "Внимание!");
		return;
	}

	fl = true;
	for (int i = 0; i < index; i++) {
		if (id == dataGridView1->Rows[i]->Cells[0]->Value->ToString()) {
			fl = false;
			break;
		}
	}

	if (!fl) {
		MessageBox::Show("Вы ввели некорректные данные! ID должен быть различен", "Внимание!");
		return;
	}
	dbConnection->Open();//открываем соединение
	String^ query = "INSERT INTO [Database31] VALUES ("+ id+",'"+ Tarif +"',"+ Price +", "+ Discount +")";//запрос
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);//команда
	
	//запрос
	if (dbComand->ExecuteNonQuery() != 1) {
		MessageBox::Show("Ошибка выполнения вашего запроса","Ошибка");
	}
	else {
		MessageBox::Show("Данные добавлены");

	}
	

	dbConnection->Close();
	
	return System::Void();
}

System::Void Project2::MyForm1::button_update_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выберите одну строку для добавления");
		return;
	}int index = dataGridView1->SelectedRows[0]->Index;

	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr) {
		MessageBox::Show("не все данные введены");
		return;
	}
	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();
	String^ Tarif = dataGridView1->Rows[index]->Cells[1]->Value->ToString();
	String^ Price = dataGridView1->Rows[index]->Cells[2]->Value->ToString();
	String^ Discount = dataGridView1->Rows[index]->Cells[3]->Value->ToString();
	String^ connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Database31.mdb";//подключились
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	
	dbConnection->Open();//открываем соединение
	String^ query = "UPDATE [Database31] SET Tarif='" + Tarif + "',Price=" + Price + ", Discount=" + Discount + " WHERE id= " + id;//запрос
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);//команда

	//запрос
	if (dbComand->ExecuteNonQuery() != 1) {
		MessageBox::Show("Ошибка выполнения вашего запроса", "Ошибка");
	}
	else {
		MessageBox::Show("Данные изменены");

	}


	dbConnection->Close();

	return System::Void();
}

System::Void Project2::MyForm1::button_delete_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выберите только одну строку!", "Внимание!");
		return;
	}
	int index = dataGridView1->SelectedRows[0]->Index;

	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();

	String^ connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Database31.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "DELETE FROM [Database31] WHERE id = " + id;
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);



	if (dbCommand->ExecuteNonQuery() != 1) {
		MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
	}
	else {
		MessageBox::Show("Данные удалены!", "Готово!");
		dataGridView1->Rows->RemoveAt(index);
	}

	dbConnection->Close();
	return System::Void();
	
}

System::Void Project2::MyForm1::button_sort_Click(System::Object^ sender, System::EventArgs^ e)
{
	dataGridView1->Rows->Clear();

	String^ connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Database31.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "SELECT * FROM [Database31] ORDER BY Discount";
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader();

	if (dbReader->HasRows == false) {
		MessageBox::Show("Ошибка!", "Ошибка!");
	}
	else {
		while (dbReader->Read()) {
			dataGridView1->Rows->Add(dbReader["id"], dbReader["Tarif"], dbReader["Price"], dbReader["Discount"]);
		}
	}

	dbReader->Close();
	dbConnection->Close();
	return System::Void();
}
