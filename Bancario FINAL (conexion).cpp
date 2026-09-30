#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;

void setcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    int opcion;

    do {
        system("cls");

        setcolor(11);
        cout << "==================================================" << endl;
        cout << "   CALCULADORA DE CUOTA BANCARIA - RD" << endl;
        setcolor(7);
        cout << "   Cuota Fija + Interes + Seguro" << endl;
        setcolor(10);
        cout << "   Autor: Michael" << endl;
        setcolor(11);
        cout << "==================================================" << endl;
        setcolor(7);
        cout << "  1. Nueva simulacion de prestamo" << endl;
        cout << "  2. Ver historial" << endl;
        cout << "  3. Salir" << endl;
        setcolor(11);
        cout << "==================================================" << endl;
        setcolor(7);
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string cliente;
            double monto, tasaAnual, seguroPct, comisionPct;
            int meses;

            cout << "\nNombre del cliente: ";
            cin.ignore();
            getline(cin, cliente);

            cout << "Monto del prestamo (RD$): ";
            cin >> monto;

            cout << "Tasa de interes anual (%): ";
            cin >> tasaAnual;

            cout << "Plazo en meses: ";
            cin >> meses;

            cout << "Porcentaje de seguro mensual (ej: 0.05): ";
            cin >> seguroPct;

            cout << "Comision de apertura (%): ";
            cin >> comisionPct;

            if (monto <= 0 || meses <= 0 || tasaAnual < 0) {
                setcolor(12);
                cout << "\nDatos invalidos." << endl;
                setcolor(7);
                cout << "\nPresione ENTER...";
                cin.ignore();
                cin.get();
                continue;
            }

            // ---------- CALCULOS ----------
            double comision = monto * (comisionPct / 100.0);
            double montoNeto = monto - comision;
            double r = tasaAnual / 12.0 / 100.0;
            double cuotaBase;

            if (r == 0) {
                cuotaBase = monto / meses;
            } else {
                cuotaBase = monto * (r * pow(1 + r, meses)) / (pow(1 + r, meses) - 1);
            }

            double seguroMensual = monto * (seguroPct / 100.0);
            double cuotaTotal = cuotaBase + seguroMensual;
            double interesesTotales = (cuotaBase * meses) - monto;
            double totalPagar = (cuotaTotal * meses) + comision;

            // ---------- FACTURA ----------
            system("cls");
            cout << fixed << setprecision(2);

            setcolor(11);
            cout << "==============================================================" << endl;
            cout << "          FACTURA / SIMULACION DE PRESTAMO BANCARIO" << endl;
            cout << "                   REPUBLICA DOMINICANA" << endl;
            cout << "==============================================================" << endl;
            setcolor(7);

            time_t ahora = time(0);
            tm* ltm = localtime(&ahora);
            cout << " Fecha: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;

            setcolor(10);
            cout << " Cliente: " << cliente << endl;
            setcolor(7);

            setcolor(11);
            cout << "--------------------------------------------------------------" << endl;
            setcolor(14);
            cout << " DATOS DEL PRESTAMO" << endl;
            setcolor(7);
            cout << "   Monto solicitado:           RD$ " << setw(12) << monto << endl;
            cout << "   Comision de apertura:       RD$ " << setw(12) << comision << endl;
            cout << "   Monto neto recibido:        RD$ " << setw(12) << montoNeto << endl;
            cout << "   Tasa de interes anual:      " << setw(10) << tasaAnual << " %" << endl;
            cout << "   Plazo:                      " << setw(10) << meses << " meses" << endl;
            cout << "   Seguro desgravamen:         " << setw(10) << seguroPct << " % mensual" << endl;

            setcolor(11);
            cout << "--------------------------------------------------------------" << endl;
            setcolor(14);
            cout << " DESGLOSE DE LA CUOTA MENSUAL" << endl;
            setcolor(7);
            cout << "   Cuota base (Capital+Interes): RD$ " << setw(12) << cuotaBase << endl;
            cout << "   + Seguro de vida:             RD$ " << setw(12) << seguroMensual << endl;
            cout << "   --------------------------------------------" << endl;

            setcolor(10);
            cout << "   CUOTA TOTAL MENSUAL:          RD$ " << setw(12) << cuotaTotal << endl;
            setcolor(7);

            setcolor(11);
            cout << "--------------------------------------------------------------" << endl;
            setcolor(14);
            cout << " RESUMEN DEL COSTO TOTAL" << endl;
            setcolor(7);
            cout << "   Intereses totales:          RD$ " << setw(12) << interesesTotales << endl;
            cout << "   ITBIS sobre intereses:      RD$ " << setw(12) << 0.00;
            setcolor(10);
            cout << " (EXENTO - DGII)" << endl;
            setcolor(7);
            cout << "   Comision de apertura:       RD$ " << setw(12) << comision << endl;
            cout << "   Seguro total:               RD$ " << setw(12) << (seguroMensual * meses) << endl;
            cout << "   --------------------------------------------" << endl;

            setcolor(13);
            cout << "   TOTAL A PAGAR AL FINAL:      RD$ " << setw(12) << totalPagar << endl;
            setcolor(7);

            setcolor(11);
            cout << "==============================================================" << endl;
            setcolor(7);
            cout << " Nota: Segun DGII los intereses de prestamos estan EXENTOS de ITBIS." << endl;
            setcolor(11);
            cout << "==============================================================" << endl;
            setcolor(7);

            // ---------- TABLA DE AMORTIZACION COMPLETA ----------
            cout << "\n";
            setcolor(11);
            cout << "============== TABLA DE AMORTIZACION ==============" << endl;
            setcolor(7);
            cout << left << setw(6) << "Mes"
                 << right << setw(14) << "Cuota Base"
                 << setw(14) << "Interes"
                 << setw(14) << "Capital"
                 << setw(16) << "Saldo" << endl;
            cout << "----------------------------------------------------" << endl;

            double saldo = monto;
            for (int mes = 1; mes <= meses; mes++) {
                double interes = saldo * r;
                double capital = cuotaBase - interes;
                if (capital > saldo) capital = saldo;
                saldo -= capital;
                if (saldo < 0.01) saldo = 0;

                cout << left << setw(6) << mes
                     << right << setw(14) << cuotaBase
                     << setw(14) << interes
                     << setw(14) << capital
                     << setw(16) << saldo << endl;
            }
            cout << "----------------------------------------------------" << endl;
            cout << "Nota: Cuota total = Cuota Base + Seguro mensual" << endl;

            // ---------- GUARDAR HISTORIAL ----------
            ofstream archivo("historial_prestamos.txt", ios::app);
            if (archivo.is_open()) {
                archivo << fixed << setprecision(2);
                archivo << "========================================\n";
                archivo << "Cliente: " << cliente << "\n";
                archivo << "Monto: RD$ " << monto << "\n";
                archivo << "Tasa: " << tasaAnual << "% | Plazo: " << meses << " meses\n";
                archivo << "Cuota Total Mensual: RD$ " << cuotaTotal << "\n";
                archivo << "Total a pagar: RD$ " << totalPagar << "\n";
                archivo << "ITBIS: EXENTO\n";
                archivo << "========================================\n\n";
                archivo.close();
                setcolor(10);
                cout << "\nSimulacion guardada en historial_prestamos.txt" << endl;
                setcolor(7);
            }

            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }
        else if (opcion == 2) {
            ifstream archivo("historial_prestamos.txt");
            if (!archivo.is_open()) {
                setcolor(12);
                cout << "\nNo hay historial todavia." << endl;
                setcolor(7);
            } else {
                setcolor(11);
                cout << "\n============== HISTORIAL ==============\n" << endl;
                setcolor(7);
                string linea;
                while (getline(archivo, linea)) {
                    cout << linea << endl;
                }
                archivo.close();
            }
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }
        else if (opcion == 3) {
            setcolor(10);
            cout << "\nGracias por usar la calculadora.\n" << endl;
            setcolor(7);
        }
        else {
            setcolor(12);
            cout << "\nOpcion no valida." << endl;
            setcolor(7);
            cout << "\nPresione ENTER...";
            cin.ignore();
            cin.get();
        }

    } while (opcion != 3);

    return 0;
}
