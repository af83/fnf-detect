#include <ccv.h>


const double hair_offset = 0.25;


int main(int argc, char **argv) {
	ccv_enable_default_cache();
	ccv_dense_matrix_t* image = NULL;
	ccv_scd_classifier_cascade_t* cascade = ccv_scd_classifier_cascade_read(CASCADE_PATH);

	if (argc < 2) {
		fprintf(stderr, "Usage: fnf-detect image\nVersion: %s - ccv\n", VERSION);
		return -1;
	}

	if (cascade == NULL) {
		fprintf(stderr, "Error: can't find the cascade file %s\n", CASCADE_PATH);
		return -1;
	}

	ccv_read(argv[1], &image, CCV_IO_GRAY | CCV_IO_ANY_FILE);
	if (image == NULL) {
		fprintf(stderr, "Error: can't read %s\n", argv[1]);
		return -1;
	}

	ccv_array_t* seq = ccv_scd_detect_objects(image, &cascade, 1, ccv_scd_default_params);
	for (int i = 0; i < seq->rnum; i++) {
		ccv_comp_t* comp = (ccv_comp_t*) ccv_array_get(seq, i);
		int y = comp->rect.y - hair_offset * comp->rect.height;
		if (y < 0) y = 0;
		printf("%d %d %d %d face\n", comp->rect.x, y, comp->rect.width, comp->rect.height);
	}

	ccv_array_free(seq);
	ccv_matrix_free(image);
	ccv_scd_classifier_cascade_free(cascade);
	ccv_disable_cache();

	return 0;
}
