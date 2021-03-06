/*
 * helpere.hpp -- help encoding images
 * by pts@fazekas.hu at Tue Dec  9 10:53:21 CET 2003
 */

/* Don't use this here, because we don't have helpere.cpp
#ifdef __GNUC__
#ifndef __clang__
#pragma interface
#endif
#endif
*/

#ifndef HELPERE_HPP
#define HELPERE_HPP 1

#include "image.hpp"
#include "error.hpp"
#include "gensio.hpp"

/** Ugly multiple inheritance. !! unify with PNG, TIFF etc. */
class HelperE: public Filter::NullE, public Filter::PipeE {
 public:
  inline HelperE(char const*filter_cmd, char const*mainfn=NULL): Filter::NullE(), Filter::PipeE(*(Filter::NullE*)this, filter_cmd, (slendiff_t)mainfn) {
    /* ^^^ (slendiff_t) is unsafe cast */
    // GenBuffer::Writable &out_, char *pipe_tmpl, slendiff_t i=0)
  }
  inline virtual void vi_copy(FILE *f) {
    // img=Image::load("-", SimBuffer::B(), (Image::filep_t)f, (char const*)"PNM");
    Filter::UngetFILED ufd((char const*)NULLP, f, Filter::UngetFILED::CM_closep|Filter::UngetFILED::CM_keep_stdinp);
    img=Image::load((Image::Loader::UFD*)(long)&ufd, SimBuffer::B(), (char const*)"PNM");
    /* We must close f, this is part of the vi_copy contract. If we fail to
     * close it, cleanup_remove won't be able to remove the tmp files at
     * Error::runCleanups() time.
     */
    fclose(f);
  }
  inline Image::Sampled *getImg() const { return img; }
 protected:
  Image::Sampled *img;
};

#endif
