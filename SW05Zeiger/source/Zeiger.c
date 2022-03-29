/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MCCarSkeleton.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();


	// POINTER --------------------------------------------------
	/*
	 printf("Hello World\n");
	 int g;
	 int h;

	 int* z;
	 z = malloc(sizeof(float));
	 if(z) {
	 *z = 7;
	 g = *z * 27;
	 h = &z;
	 }
	 printf("z %d\n", *z);
	 printf("g %d\n", g);
	 printf("h %d\n", h);
	 */

	typedef struct Node {
		struct Node *prev;
		struct Node *next;
		int data;
	} Node;

	void newNode(Node *oldNode, Node *newNode) {
		oldNode->next = newNode;
		newNode->prev = oldNode;
		newNode->next = NULL;
	}

	Node *root = malloc(sizeof(Node));
	if (root == NULL)
		return;
	root->data = 0;
	root->prev = NULL;
	root->next = NULL;

	Node *nodeUno = malloc(sizeof(Node));
	nodeUno->data = 1;
	nodeUno->prev = root;
	root->next = nodeUno;

	Node *nodeDos = malloc(sizeof(Node));
	nodeDos->data = 2;
	nodeDos->prev = nodeUno;
	nodeUno->next = nodeDos;

	Node *nodeTres = malloc(sizeof(Node));
	//nodeTres->prev = nodeDos;
	nodeTres->next = NULL;
	nodeTres->data = 3;


	newNode(root, nodeUno);
	newNode(nodeUno, nodeDos);
	newNode(nodeDos, nodeTres);

	void printNode(Node *node) {
		printf("Data: %d - ", node->data);
		printf("Prev: %d - ", node->prev->data);
		printf("Next: %d \n", node->next->data);
	}
	printNode(root);
	printNode(nodeUno);
	printNode(nodeDos);
	printNode(nodeTres);



	// MATRIZEN -------------------------------------------------------


	double** createMatrix(int x, int y, double values){
		double matrix[x][y];
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; y++){
				matrix[i][j] = values;
			}
		}
		return *matrix;
	}

	double **m;
	m = createMatrix(3,4,3.0);

	void printMatrix(double** m, int x, int y){
		for(int i = 0; i < x; i++){
					for(int j = 0; j < y; y++){
						printf("%d", m[i][j]);
					}
				}
	}
	printMatrix(m,3,4);










}
