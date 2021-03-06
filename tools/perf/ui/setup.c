#include "../cache.h"
#include "../debug.h"


void setup_browser(bool fallback_to_pager)
{
	if (!isatty(1) || dump_trace)
		use_browser = 0;

	/* default to TUI */
	if (use_browser < 0)
		use_browser = 1;

	switch (use_browser) {
	case 2:
		if (perf_gtk__init() == 0)
			break;
		/* fall through */
	case 1:
		use_browser = 1;
		if (ui__init() == 0)
			break;
		/* fall through */
	default:
		use_browser = 0;
		if (fallback_to_pager)
			setup_pager();
		break;
	}
}

void exit_browser(bool wait_for_ok)
{
	switch (use_browser) {
	case 2:
		perf_gtk__exit(wait_for_ok);
		break;

	case 1:
		ui__exit(wait_for_ok);
		break;

	default:
		break;
	}
}
