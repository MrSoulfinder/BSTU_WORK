#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;

int Asmb_str()
{
    _asm {
        model small
        .stack 100h
        .data
        mes1 db "Vvedite stroky: $"
        mes3 db 0ah, 0dh, "Kol-vo povtoreniy vvedennogo simvola: $"
        mes4 db 0ah, 0dh, "Vvedite proizvonuy simvol dlya sravneniya: $"
        mes5 db 0ah, 0dh, "Simvol nekorrekten: $"
        string db 10 dup("$")
        len_string = $ - string
        adr_string dd string
        .code
        main :
        mov ax, @data
            mov ds, ax
            xor ax, ax
            mov ah, 09h; ������� � ah 09h
            lea dx, mes1; � dx �������� ������ mes1
            int 21h; ����� ���������� DOS ��� ������ ������
            mov cx, len_string; � cx ������� ����� ������
            dec cx; ��������� �� * 1 ������� cx
            les di, adr_string; � di ��������, � es ���������� ������
            m1 :
        mov ah, 01h; � ah ������� 01h
            int 21h; � AL - ������, ���������� �� ������������ �����*
            cmp al, 0dh; ��������� ������� Enter
            je prov; ���� ����� ������� �� ����� prov
            cmp al, 0; ���������� al � ����
            jne m2; ���� �� ����� ������� �� ����� m2
            jmp prov; ������� �� ����� prov
            m2 :
        stosb; ������������ ���������� AL � ������ ������ � �������� ES : (E)DI, ����� ���� ���������� ������� �(E)DI.

            loop m1; ��������� m1, ����* cx �� ������ ������ ����
            prov :
        mov cx, len_string; � cx ������� ����� ������
            dec cx; ��������� cx �� �������
            mov si, 0; ��������� ���������� �������� si** � ������ ������
            exit :

        lea dx, mes4
            mov ah, 09h
            int 21h
            mov ah, 01h
            int 21h
            cmp al, 0
            je not2
            go :
        cmp string[si], al
            jne go1
            inc bh
            go1 :
        inc si
            loop go
            lea dx, mes3
            mov ah, 09h
            int 21h
            add bh, "0"
            mov dl, bh
            mov ah, 02h
            int 21h
            jmp ex
            not2 :
        lea dx, mes5
            mov ah, 09h
            int 21h
            ex :
        mov ax, 4c00h
            mov ah, 10h

            mov ah, 0
            int 16h

            mov ah, 4Ch
            int 21h
            end main
    }
    return 0;
}

int main()
{
    Asmb_str();
    return 0;
}
