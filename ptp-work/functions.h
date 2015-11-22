void intro(){
	system("clear");
	printf("Bem vindo ao programa!\n");
	printf("Dígite o nome do seu arquivo (sem extensão)");
	printf("\t(Exemplo: lena)\n");
}

void read_image(Pixel image[lat][lat], FILE *imagepath){
	int i, j;
	
	null_matrix(image);
	if(filetype[0] == 'P' && filetype[1] == '3')
        for(i = 0; i < height; i++)
        	for(j = 0; j < width; j++)
        		fscanf(imagepath, "%i %i %i", &image[i][j].red, &image[i][j].green, &image[i][j].blue);
    else {
    	system("clear");
    	printf("O tipo de arquivo PPM não é P3!\n");
    	exit(1);
    }

    fclose(imagepath);

}

void create_new_file(Pixel image[lat][lat]){
	int i, j;
	FILE *newfile;
	newfile = fopen(name, "w");
	fprintf(newfile, "%s\n%i %i\n%i\n", filetype, width, height, clrRange);
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
        		fprintf(newfile, "%i %i %i ", image[i][j].red, image[i][j].green, image[i][j].blue);

    system("clear");
    printf("O arquivo %s foi criado com sucesso na pasta raíz do programa.\n", name);
}

void null_matrix(Pixel image[lat][lat]){
	int i, j;
	for(i = 0; i < lat; i++)
		for(j = 0; j < lat; j++){
			image[i][j].blue = 0;
			image[i][j].red = 0;
			image[i][j].green = 0;
		}
}

void rotation_controller(Pixel image[lat][lat]){
	int ang;
	printf("Digite o angulo de rotação (em sentido horario):\n");
	scanf("%i", &ang);
	switch (ang){
		case 90:
			strcat(name, "_rot_90.ppm");
			ef_rotate_left(image);
			ef_rotate_left(image);
			ef_rotate_left(image);
			break;
		case 180:
			strcat(name, "_rot_180.ppm");
			ef_rotate_left(image);
			ef_rotate_left(image);
			break;
		case 270:
			strcat(name, "_rot_270.ppm");
			ef_rotate_left(image);
			break;
		default:
			system("clear");
			printf("Escolha um angulo reto: 90 - 180 - 270 \n");
			rotation_controller(image);			
	}
}

void choose_options(Pixel image[lat][lat]){
	int choice;
	
	printf("\n======== Escolha uma opção =======\n");
	printf("1 - thr     //    Thresholding   *\n");
	printf("2 - blur    //    Blurring       *\n");
	printf("3 - sha     //    Sharpening     *\n");
	printf("4 - rot     //    Rotacionar     *\n");
	printf("5 - amp     //    Ampliar        *\n");
	printf("6 - red     //    Reduzir        *\n");
	printf("==================================\n");

	printf("============= Extras =============\n");
	printf("10 - bw     //    Preto e Branco *\n");
	printf("11 - Mir    //    Espelhar       *\n");
	printf("12 - borda  //    Detecta Bordas *\n");
	printf("13 - inv    //    Negativo       *\n");
	printf("14 - sep    //    Tom de sepia   *\n");
	printf("==================================\n");

	scanf("%i", &choice);
	controller(choice, image);
}

void controller(int choice, Pixel image[lat][lat]){
	switch(choice){
		case THR:
			int grau;
			printf("Insira o padrão de binarização entre 0 e 255 (Padrão = 127)\n");
			scanf("%i", &grau);
			sprintf(nameFile, "_thr_%i.ppm", grau);
			strcat(name, nameFile);
			ef_thresholding(image, grau);
			break;

		case BLU:
			strcat(name, "_blur.ppm");
			ef_blur(image);
			break;

		case SHAR:
			strcat(name, "_shar.ppm");
			ef_sharpening(image);
			break;

		case ROT:
			system("clear");
			rotation_controller(image);
			break;

		case AMP:
			int grau;
			printf("Quantas vezes deseja ampliar a imagem?\n");
			scanf("%i", &grau);
			sprintf(nameFile, "_amp_%i.ppm", grau);
			strcat(name, nameFile);
			ef_enlarge(image, grau);
			break;

		case RED:
			int grau;
			printf("Quantas vezes deseja reduzir a imagem?\n");
			scanf("%i", &grau);
			sprintf(nameFile, "_red_%i.ppm", grau);
			strcat(name, nameFile);
			ef_reduce(image, grau);
			break;

		case BW:
			strcat(name, "_bw.ppm");
			ef_black_white(image);
			break;

		case MIR:
			strcat(name, "_mir.ppm");
			ef_horizontal_mirror(image);
			break;

		case BORD:
			strcat(name, "_bordas.ppm");
			ef_border_detection(image);
			break;

		case INV:
			strcat(name, "_neg.ppm");
			ef_negative(image, clrRange);
			break;

		case SEP:
			strcat(name, "_sepia.ppm");
			ef_sepia(image);
			break;

		default:
			system("clear");
			printf("Essa opcao nao existe, tente novamente.\n\n");
			choose_options(image);
			break;
	}
}
