#include "xmlcfg.h"

int joystick_load_config(const char filename[]){
	scew_reader *reader = NULL;
	scew_parser *parser = NULL;
	scew_tree *tree = NULL;

	/* Creates an SCEW parser. This is the first function to call. */
	parser = scew_parser_create();

	scew_parser_ignore_whitespaces(parser, SCEW_TRUE);

	/* Loads an XML file. */
	reader = scew_reader_file_create(filename);
	if (reader == NULL) {
		scew_error code = scew_error_code();
		scew_printf(_XT("Unable to load file (error #%d: %s)\n"), code,
				scew_error_string(code));
	}

	tree = scew_parser_load(parser, reader);
	if (tree == NULL) {
		scew_error code = scew_error_code();
		scew_printf(_XT("Unable to parse file (error #%d: %s)\n"), code,
				scew_error_string(code));
		if (code == scew_error_expat) {
			enum XML_Error expat_code = scew_error_expat_code(parser);
			scew_printf(_XT("Expat error #%d (line %d, column %d): %s\n"),
					expat_code, scew_error_expat_line(parser),
					scew_error_expat_column(parser),
					scew_error_expat_string(expat_code));
		}

		/* Frees the SCEW parser and reader. */
		scew_reader_free(reader);
		scew_parser_free(parser);

		return EXIT_FAILURE;
	}

	scew_element *MENU_DOWN = scew_element_by_name(scew_tree_root(tree),"MENU_DOWN");

	printf("KEY:%s \n", scew_element_name(MENU_DOWN));
	printf("VAL:%s \n", scew_attribute_value(scew_element_attribute_by_name(MENU_DOWN,"key")));

	/* Free every SCEW variable */
	scew_reader_free(reader);
	scew_parser_free(parser);
	scew_tree_free(tree);

	return 0;
}
