#include "nftracker.h"
#include "config.h"
#include "bstrlib.h"
#include "common.h"
#include "util-search.h"

extern globalconfig config;

int init_sigs (void)
{
    add_sig_pdf();
    add_sig_zip();
    add_sig_html();
    add_sig_doc();
    add_sig_exe();
    //add_sig_exe();
    return 0;
}

int add_sig_file (signature *sig)
{
    signature *tail;
    tail = config.sig_file;
    if (config.sig_file == NULL) {
        config.sig_file = sig;
        return 0;
    }
    while (tail->next != NULL) {
        tail = tail->next;
    }
    if (tail->next == NULL ) {
        tail->next = sig;
        return 0;
    }
    return 1;
}

int add_sig_pdf(void)
{
    const char *err = NULL;     /* PCRE */
    int erroffset;              /* PCRE */
    bstring pcre_start = NULL;
    bstring pcre_stop = NULL;
    signature *sig;

    sig = (signature *) calloc(1, sizeof(signature));

    sig->next = NULL;
    sig->prev = NULL;
    pcre_start = bfromcstr("\x25\x50\x44\x46");     // %PDF
    pcre_stop = bfromcstr("\x25\x45\x4F\x46");  // %EOF\r
    sig->filetype = bfromcstr("pdf");

    sig->regex_start = pcre_compile((char *)bdata(pcre_start), 0, &err, &erroffset, NULL);
    sig->regex_stop = pcre_compile((char *)bdata(pcre_stop), 0, &err, &erroffset, NULL);
    sig->study_start = pcre_study(sig->regex_start, 0, &err);
    sig->study_stop = pcre_study(sig->regex_stop, 0, &err);

    add_sig_file(sig);
    bdestroy(pcre_start);
    bdestroy(pcre_stop);
    return 0;
}

int add_sig_zip(void)
{
    const char *err = NULL;     /* PCRE */
    int erroffset;              /* PCRE */
    bstring pcre_start = NULL;
    bstring pcre_stop = NULL;
    signature *sig;

    sig = (signature *) calloc(1, sizeof(signature));

    sig->next = NULL;
    sig->prev = NULL;
    pcre_start = bfromcstr("\x50\x4B\x03\x04");    
    pcre_stop = bfromcstr("\x3c\xac");  
    sig->filetype = bfromcstr("zip");

    sig->regex_start = pcre_compile((char *)bdata(pcre_start), 0, &err, &erroffset, NULL);
    sig->regex_stop = pcre_compile((char *)bdata(pcre_stop), 0, &err, &erroffset, NULL);
    sig->study_start = pcre_study(sig->regex_start, 0, &err);
    sig->study_stop = pcre_study(sig->regex_stop, 0, &err);

    add_sig_file(sig);
    bdestroy(pcre_start);
    bdestroy(pcre_stop);
    return 0;
}

int add_sig_html(void)
{
    const char *err = NULL;     /* PCRE */
    int erroffset;              /* PCRE */
    bstring pcre_start = NULL;
    bstring pcre_stop = NULL;
    signature *sig;

    sig = (signature *) calloc(1, sizeof(signature));

    sig->next = NULL;
    sig->prev = NULL;
    pcre_start = bfromcstr("\x3Chtml"); // <html
    pcre_stop = bfromcstr("\x3C\x2Fhtml\x3E"); // </html>
    sig->filetype = bfromcstr("html");

    sig->regex_start = pcre_compile((char *)bdata(pcre_start), 0, &err, &erroffset, NULL);
    sig->regex_stop = pcre_compile((char *)bdata(pcre_stop), 0, &err, &erroffset, NULL);
    sig->study_start = pcre_study(sig->regex_start, 0, &err);
    sig->study_stop = pcre_study(sig->regex_stop, 0, &err);

    add_sig_file(sig);
    bdestroy(pcre_start);
    bdestroy(pcre_stop);
    return 0;
}

int add_sig_doc(void)
{
    const char *err = NULL;     /* PCRE */
    int erroffset;              /* PCRE */
    bstring pcre_start = NULL;
    bstring pcre_stop = NULL;
    signature *sig;

    sig = (signature *) calloc(1, sizeof(signature));

    sig->next = NULL;
    sig->prev = NULL;
    pcre_start = bfromcstr("\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1");
    pcre_stop = bfromcstr("THISMUSTNOTEXISTEVER");
    sig->filetype = bfromcstr("doc");

    sig->regex_start = pcre_compile((char *)bdata(pcre_start), 0, &err, &erroffset, NULL);
    sig->regex_stop = pcre_compile((char *)bdata(pcre_stop), 0, &err, &erroffset, NULL);
    sig->study_start = pcre_study(sig->regex_start, 0, &err);
    sig->study_stop = pcre_study(sig->regex_stop, 0, &err);

    add_sig_file(sig);
    bdestroy(pcre_start);
    bdestroy(pcre_stop);
    return 0;
}

int add_sig_exe(void)
{
    const char *err = NULL;     /* PCRE */
    int erroffset;              /* PCRE */
    bstring pcre_start = NULL;
    bstring pcre_stop = NULL;
    signature *sig;

    sig = (signature *) calloc(1, sizeof(signature));

    sig->next = NULL;
    sig->prev = NULL;
    pcre_start = bfromcstr("\x4D\x5A");
    pcre_stop = bfromcstr("This program cannot be run in DOS mode.");
    sig->filetype = bfromcstr("exe");

    sig->regex_start = pcre_compile((char *)bdata(pcre_start), 0, &err, &erroffset, NULL);
    sig->regex_stop = pcre_compile((char *)bdata(pcre_stop), 0, &err, &erroffset, NULL);
    sig->study_start = pcre_study(sig->regex_start, 0, &err);
    sig->study_stop = pcre_study(sig->regex_stop, 0, &err);

    add_sig_file(sig);
    bdestroy(pcre_start);
    bdestroy(pcre_stop);
    return 0;
}

