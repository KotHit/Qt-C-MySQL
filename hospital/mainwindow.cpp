#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Server name / database name
        QString server="PASHA-ПК\\SQLEXPRESS";
        QString dbname="testdb";
    //Connect to database
        db = QSqlDatabase::addDatabase("QODBC3");
        db.setDatabaseName("Driver={SQL Server Native Client 11.0};Server=PASHA-ПК\\SQLEXPRESS;Database=test2;Uid=kot2;Pwd=admin;");
    //Checking
        if (!db.open()) {
           qDebug()<<"Not opened " +db.lastError().text();
        }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_create_clicked()
{
    //create database
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("create table patient ("
                  "Id_pat int primary key not null,"
                  "Id_ser int not null,"
                  "Name_pat varchar(20),"
                  "Age int,"
                  "State varchar(20),"
                  "Diagnosis varchar(20),"
                  "Foreign key (Id_ser) references service (Id_ser)"
                  " );")){
        QMessageBox::information(this,"DB","DataBase Create");

    }
    else{
        QMessageBox::information(this,"DB","Database is`t cteated "+query.lastError().text());
    }
}

void MainWindow::on_bt_open_clicked()
{
    //new table model
        model=new QSqlRelationalTableModel(this,db);
        //cash strategy
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setTable("patient");
       //Relation with two tables
        model->setRelation(model->fieldIndex("Id_ser"),QSqlRelation("service","Id_ser","Serv"));
        //select all on begin program run
        model->select();

    ui->tableView->setModel(model);
    //Tab View with ComboBox
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    ui->comboBox_pat->setModel(model);
    ui->comboBox_pat->setModelColumn(model->fieldIndex("Name_pat"));
}

void MainWindow::on_bt_submit_clicked()
{
    model->submitAll();
}

void MainWindow::on_bt_add_clicked()
{
//    qDebug()<<"Insert ";
//    model->insertRow(model->rowCount());

    QString id,serv,name,age,state,diag;
    id=ui->le_id_add->text();
    serv=ui->le_serv_add->text();
    name=ui->le_name_add->text();
    age=ui->le_age_add->text();
    state=ui->le_state_add->text();
    diag=ui->le_diag_add->text();
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("insert into patient values('"+id+"','"+serv+"','"+name+"', '"+age+"','"+state+"','"+diag+"');")){
        QMessageBox::information(this,"DB","Insert");
    }
    else{
        QMessageBox::information(this,"DB","does not insert");
    }
}

void MainWindow::on_bt_delete_clicked()
{
//    int select=ui->tableView->currentIndex().row();
//    if(select>=0){
//        qDebug()<<"Delete record ";
//        model->removeRow(select);
//    }
    /*if(query.exec( Create view Tab AS Select * from patient ))*/
    QString id=ui->le_id_add->text();
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("Delete from patient where Id_pat='"+id+"';")){
        QMessageBox::information(this,"DB","Delete");
    }
    else{
        QMessageBox::information(this,"DB","does not Delete "+query.lastError().text());
    }
}

void MainWindow::on_bt_revert_clicked()
{
    model->revertAll();
}

void MainWindow::on_bt_create_doc_clicked()
{
    //create database
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("create table doctor ("
                  "Id_doc int primary key not null,"
                  "Doc varchar(20),"
                  "Experience int,"
                  "Specialty varchar(20)"
                  " );")){
        QMessageBox::information(this,"DB","DataBase Create");

    }
    else{
        QMessageBox::information(this,"DB","Database is`t cteated "+query.lastError().text());
    }
}

void MainWindow::on_bt_drop_pat_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("drop table patient;")){
        QMessageBox::information(this,"DB","Database Droped");
    }
    else{
        QMessageBox::information(this,"DB","Eror droped "+ query.lastError().text());
    }
}

void MainWindow::on_bt_create_ser_clicked()
{
    //create database
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("create table service ("
                  "Id_ser int primary key not null,"
                  "Serv varchar(20),"
                  "Surcharge int"
                  " );")){
        QMessageBox::information(this,"DB","DataBase Create");

    }
    else{
        QMessageBox::information(this,"DB","Database is`t cteated "+query.lastError().text());
    }
}

void MainWindow::on_bt_open_ser_clicked()
{
    //new table model
        model=new QSqlRelationalTableModel(this,db);
        //cash strategy
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setTable("service");
        //select all on begin program run

        model->select();
    ui->tableView_3->setModel(model);
}

void MainWindow::on_bt_drop_ser_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("drop table service;")){
        QMessageBox::information(this,"DB","Database Droped");
    }
    else{
        QMessageBox::information(this,"DB","Eror droped "+ query.lastError().text());
    }
}

void MainWindow::on_bt_submit_ser_clicked()
{
    qDebug()<<"Submin all ";
    model->submitAll();
}

void MainWindow::on_bt_revert_ser_clicked()
{
    qDebug()<<"Revert ";
    model->revertAll();
}

void MainWindow::on_bt_add_ser_clicked()
{
    qDebug()<<"Add ";
    model->insertRow(model->rowCount());
}

void MainWindow::on_bt_delete_ser_clicked()
{
    int select=ui->tableView_3->currentIndex().row();
    if(select>=0){
        qDebug()<<"Delete ";
        model->removeRow(select);
    }
}

void MainWindow::on_bt_open_doc_clicked()
{
    //new table model
        model=new QSqlRelationalTableModel(this,db);
        //cash strategy
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setTable("doctor");
        //select all on begin program run

        model->select();
    ui->tableView_4->setModel(model);


}

void MainWindow::on_bt_add_doc_clicked()
{
    qDebug()<<"Insert ";
    model->insertRow(model->rowCount());
}

void MainWindow::on_bt_delete_doc_clicked()
{
    int select=ui->tableView_4->currentIndex().row();
    if(select>=0){
        qDebug()<<"Delete ";
        model->removeRow(select);
    }
}

void MainWindow::on_bt_submit_doc_clicked()
{
    qDebug()<<"Submit ";
    model->submitAll();
}

void MainWindow::on_bt_revert_doc_clicked()
{
    qDebug()<<"Revert";
    model->revertAll();
}

void MainWindow::on_bt_drop_doc_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("drop table doctor;")){
        QMessageBox::information(this,"DB","Database Droped");
    }
    else{
        QMessageBox::information(this,"DB","Eror droped "+ query.lastError().text());
    }
}

void MainWindow::on_bt_create_pr_clicked()
{
    //create database
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("create table price ("
                  "Id_pr int primary key not null,"
                  "Name_drug varchar(20),"
                  "Cost int"
                  " );")){
        QMessageBox::information(this,"DB","DataBase Create");

    }
    else{
        QMessageBox::information(this,"DB","Database is`t cteated "+query.lastError().text());
    }
}

void MainWindow::on_bt_open_pr_clicked()
{
    //new table model
        model=new QSqlRelationalTableModel(this,db);
        //cash strategy
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setTable("price");
        //select all on begin program run

        model->select();
    ui->tableView_5->setModel(model);


}

void MainWindow::on_bt_add_pr_clicked()
{
    qDebug()<<"Insert";
    model->insertRow(model->rowCount());

}

void MainWindow::on_bt_delete_pr_clicked()
{
    int select=ui->tableView_5->currentIndex().row();
    if(select>=0){
        qDebug()<<"Delete ";
        model->removeRow(select);
    }

}

void MainWindow::on_bt_submit_pr_clicked()
{
    qDebug()<<"Submit ";
    model->submitAll();
}

void MainWindow::on_bt_revert_pr_clicked()
{
    qDebug()<<"Revert";
    model->revertAll();
}

void MainWindow::on_bt_drop_pr_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("drop table price;")){
        QMessageBox::information(this,"DB","Database Droped");
    }
    else{
        QMessageBox::information(this,"DB","Eror droped "+ query.lastError().text());
    }
}

void MainWindow::on_bt_create_dep_clicked()
{
    //create database
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("create table department ("
                  "Id_dep int primary key not null,"
                  "Id_doc int not null,"
                  "Id_pat int not null,"
                  "Id_pr int not null,"
                  "Depar varchar(20),"
                  "Room int,"
                  "Foreign key (Id_doc) references doctor (Id_doc),"
                  "Foreign key (Id_pat) references patient (Id_pat),"
                  "Foreign key (Id_pr) references price (Id_pr)"
                  " );")){
        QMessageBox::information(this,"DB","DataBase Create");

    }
    else{
        QMessageBox::information(this,"DB","Database is`t cteated "+query.lastError().text());
    }
}

void MainWindow::on_bt_open_dep_clicked()
{
    //new table model
        model=new QSqlRelationalTableModel(this,db);
        //cash strategy
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setTable("department");

        model->setRelation(model->fieldIndex("Id_doc"),QSqlRelation("doctor","Id_doc","Doc"));
        model->setRelation(model->fieldIndex("Id_pat"),QSqlRelation("patient","Id_pat","Name_pat"));
        model->setRelation(model->fieldIndex("Id_pr"),QSqlRelation("price","Id_pr","Name_drug"));
        //select all on begin program run

        model->select();
        ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_2));
        ui->tableView_2->setModel(model);

        ui->comboBox_dep->setModel(model);
        ui->comboBox_dep->setModelColumn(model->fieldIndex("Depar"));

}

void MainWindow::on_bt_add_dep_clicked()
{
    qDebug()<<"Insert";
    model->insertRow(model->rowCount());
}

void MainWindow::on_bt_delete_dep_clicked()
{
    int select=ui->tableView_2->currentIndex().row();
    if(select>=0){
        qDebug()<<"Delete ";
        model->removeRow(select);
    }
}

void MainWindow::on_bt_submit_dep_clicked()
{
    qDebug()<<"Submit ";
    model->submitAll();
}

void MainWindow::on_bt_revert_dep_clicked()
{
    qDebug()<<"Revert";
    model->revertAll();
}

void MainWindow::on_bt_drop_dep_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("drop table department;")){
        QMessageBox::information(this,"DB","Database Droped");
    }
    else{
        QMessageBox::information(this,"DB","Eror droped "+ query.lastError().text());
    }
}

void MainWindow::on_bt_insert_pr_clicked()
{
    QSqlQuery query=QSqlQuery(db);
    if(query.exec("Drop index index_price ON price.Cost;")){
       // if(query.exec("Create domain namedom On price (Cost);")){
        QMessageBox::information(this,"DB","Domain Success");

    }
    else{
        QMessageBox::information(this,"DB","Domain suc ");//+query.lastError().text());
    }
}

void MainWindow::on_btn_as_clicked()
{
    model_list=new QSqlQueryModel;
    model_list->setQuery("Select Name_pat, Doc,  Room, Depar, Diagnosis, State From patient, doctor, department Where patient.Id_pat=department.Id_pat and doctor.Id_doc=department.Id_doc Order By Name_pat");
    ui->tableView_6->setModel(model_list);
}

void MainWindow::on_btn_dec_clicked()
{
    model_list=new QSqlQueryModel;
    model_list->setQuery("Select Name_pat, Doc,  Room, Depar, Diagnosis, State From patient, doctor, department Where patient.Id_pat=department.Id_pat and doctor.Id_doc=department.Id_doc Order By Room");
    ui->tableView_6->setModel(model_list);
}

void MainWindow::on_btn_list_view_clicked()
{

    model_list=new QSqlQueryModel;
    model_list->setQuery("Select Name_pat, Doc,  Room, Depar, Diagnosis, State From patient, doctor, department Where patient.Id_pat=department.Id_pat and doctor.Id_doc=department.Id_doc ");
    ui->tableView_6->setModel(model_list);
//doctor inner join department On doctor.Id_doc=department.Id_doc, patient inner join department On patient.Id_pat=department.Id_pat
  }

void MainWindow::on_comboBox_pat_currentIndexChanged(const QString &arg1)
{
    QString name=ui->comboBox_pat->currentText();

    QSqlQuery query;
    query.prepare("Select * From patient where Name_pat='"+name+"'");
    if(query.exec()){
        while (query.next()) {
            ui->le_id->setText(query.value(0).toString());
            ui->le_serv->setText(query.value(1).toString());
            ui->le_name->setText(query.value(2).toString());
            ui->le_age->setText(query.value(3).toString());
            ui->le_state->setText(query.value(4).toString());
            ui->le_diag->setText(query.value(5).toString());
        }
    }
    else{
        qDebug()<<"Eror "<<query.lastError().text();
    }
}

void MainWindow::on_btn_diag_clicked()
{
    model_list=new QSqlQueryModel;
    model_list->setQuery("Select Name_pat, Doc,  Room, Depar, Diagnosis, State From patient, doctor, department Where patient.Id_pat=department.Id_pat and doctor.Id_doc=department.Id_doc Order By Diagnosis");
    ui->tableView_6->setModel(model_list);
}

void MainWindow::on_comboBox_dep_currentIndexChanged(const QString &arg1)
{

    QString name=ui->comboBox_dep->currentText();

    model_list=new QSqlQueryModel;
    model_list->setQuery("Select Specialty, Experience, Doc From doctor where Id_doc In(Select Id_doc From department where Depar='"+name+"') ");

    /* Drop index name_index ON table.pole      CREATE INDEX index_price ON price (Cost) */

    /*QSqlQuery query;
    query.prepare("Select Room From department ");
    query.exec()*/;
    ui->tableView_7->setModel(model_list);

}

void MainWindow::on_bt_update_pat_clicked()
{
    QString id,serv,name,age,state,diag;
    id=ui->le_id_add->text();
    serv=ui->le_serv_add->text();
    name=ui->le_name_add->text();
    age=ui->le_age_add->text();
    state=ui->le_state_add->text();
    diag=ui->le_diag_add->text();
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("update patient Set Id_ser='"+serv+"',Name_pat='"+name+"', Age='"+age+"',State='"+state+"',Diagnosis='"+diag+"' where Id_pat='"+id+"';")){
        QMessageBox::information(this,"DB","Update");
    }
    else{
        QMessageBox::information(this,"DB","does not update"+query.lastError().text());
    }
}

void MainWindow::on_bt_domain_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(query.exec("create domain service2 ("
                  "Id_ser2 int primary key not null,"
                  "Serv2 varchar(20),"
                  "Surcharge2 int"
                  " );")){
        QMessageBox::information(this,"DB","DataBase2 Create");

    }
    else{
        QMessageBox::information(this,"DB","Database is`t cteated "+query.lastError().text());
    }
}
