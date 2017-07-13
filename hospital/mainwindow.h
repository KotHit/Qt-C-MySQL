#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bt_create_clicked();

    void on_bt_open_clicked();

    void on_bt_submit_clicked();

    void on_bt_add_clicked();

    void on_bt_delete_clicked();

    void on_bt_revert_clicked();

    void on_bt_create_doc_clicked();

    void on_bt_drop_pat_clicked();

    void on_bt_create_ser_clicked();

    void on_bt_open_ser_clicked();

    void on_bt_drop_ser_clicked();

    void on_bt_submit_ser_clicked();

    void on_bt_revert_ser_clicked();

    void on_bt_add_ser_clicked();

    void on_bt_delete_ser_clicked();

    void on_bt_open_doc_clicked();

    void on_bt_add_doc_clicked();

    void on_bt_delete_doc_clicked();

    void on_bt_submit_doc_clicked();

    void on_bt_revert_doc_clicked();

    void on_bt_drop_doc_clicked();

    void on_bt_create_pr_clicked();

    void on_bt_open_pr_clicked();

    void on_bt_add_pr_clicked();

    void on_bt_delete_pr_clicked();

    void on_bt_submit_pr_clicked();

    void on_bt_revert_pr_clicked();

    void on_bt_drop_pr_clicked();

    void on_bt_create_dep_clicked();

    void on_bt_open_dep_clicked();

    void on_bt_add_dep_clicked();

    void on_bt_delete_dep_clicked();

    void on_bt_submit_dep_clicked();

    void on_bt_revert_dep_clicked();

    void on_bt_drop_dep_clicked();

    void on_bt_insert_pr_clicked();

    void on_btn_as_clicked();

    void on_btn_dec_clicked();

    void on_btn_list_view_clicked();

    void on_comboBox_pat_currentIndexChanged(const QString &arg1);

    void on_btn_diag_clicked();

    void on_comboBox_dep_currentIndexChanged(const QString &arg1);

    void on_bt_update_pat_clicked();

    void on_bt_domain_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlRelationalTableModel *model;
    QSqlQueryModel *model_list;
};

#endif // MAINWINDOW_H
