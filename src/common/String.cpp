#include <sstream>
#include <vector>
#include <locale>
#include <codecvt>
#include <limits>

#include "String.h"

ByteString ConversionError::formatError(ByteString::value_type const *at, ByteString::value_type const *upto)
{
	std::stringstream ss;
	ss << "Could not convert sequence to UTF-8:";
	for(int i = 0; i < 4 && at + i < upto; i++)
		ss << " " << std::hex << (unsigned int)std::make_unsigned<ByteString::value_type>::type(at[i]);
	return ss.str();
}


std::codecvt_utf8<char32_t> convert(1);

String ByteString::FromUtf8(bool ignoreError) const
{
	std::vector<String::value_type> destination = std::vector<String::value_type>(size(), String::value_type());
	std::codecvt_utf8<char32_t>::state_type state;

	ByteString::value_type const *from = data(), *from_next;
	String::value_type *to = destination.data(), *to_next;

	while(true)
	{
		std::codecvt_utf8<char32_t>::result result = convert.in(state, from, data() + size(), from_next, to, destination.data() + destination.size(), to_next);
		from = from_next;
		to = to_next;
		if(result == std::codecvt_base::ok || result == std::codecvt_base::noconv)
		{
			destination.resize(to - destination.data());
			return String(destination.data(), destination.size());
		}
		else if(result == std::codecvt_base::partial && to == destination.data() + destination.size())
		{
			String::value_type *old_data = destination.data();
			destination.resize(2 * destination.size());
			to = destination.data() + (to - old_data);
		}
		else
		{
			if(!ignoreError)
				throw ConversionError(from, data() + size());

			if(to == destination.data() + destination.size())
			{
				String::value_type *old_data = destination.data();
				destination.resize(2 * destination.size());
				to = destination.data() + (to - old_data);
			}
			*(to++) = std::make_unsigned<ByteString::value_type>::type(*(from++));
		}
	}
}

ByteString String::ToUtf8() const
{
	std::vector<ByteString::value_type> destination = std::vector<ByteString::value_type>(size(), ByteString::value_type());
	std::codecvt_utf8<char32_t>::state_type state;

	String::value_type const *from = data(), *from_next;
	ByteString::value_type *to = destination.data(), *to_next;

	while(true)
	{
		std::codecvt_utf8<char32_t>::result result = convert.out(state, from, data() + size(), from_next, to, destination.data() + destination.size(), to_next);
		from = from_next;
		to = to_next;
		if(result == std::codecvt_base::ok || result == std::codecvt_base::noconv)
		{
			destination.resize(to - destination.data());
			return ByteString(destination.data(), destination.size());
		}
		else if(result == std::codecvt_base::error)
		{
			throw ConversionError(true);
		}
		else if(result == std::codecvt_base::partial)
		{
			ByteString::value_type *old_data = destination.data();
			destination.resize(2 * destination.size());
			to = destination.data() + (to - old_data);
		}
	}
}

inline String::value_type widen_wchar(wchar_t ch)
{
	return std::make_unsigned<wchar_t>::type(ch);
}

inline bool representable_wchar(String::value_type ch)
{
	return ch < String::value_type(std::make_unsigned<wchar_t>::type(std::numeric_limits<wchar_t>::max()));
}

inline wchar_t narrow_wchar(String::value_type ch)
{
	return wchar_t(ch);
}

static thread_local struct LocaleImpl
{
	std::basic_stringstream<char> stream;
	std::basic_stringstream<wchar_t> wstream;

	LocaleImpl()
	{
		stream.imbue(std::locale::classic());
		wstream.imbue(std::locale::classic());
	}

	inline void PrepareWStream(StringBuilder &b)
	{
		wstream.flags(b.flags);
		wstream.width(b.width);
		wstream.precision(b.precision);
		wstream.fill(b.fill);
	}

	inline void FlushWStream(StringBuilder &b)
	{
		std::basic_string<wchar_t> wstr = wstream.str();
		std::vector<String::value_type> chars; // operator new?
		chars.reserve(wstr.size());
		for(wchar_t ch : wstream.str())
			chars.push_back(widen_wchar(ch));
		b.AddChars(chars.data(), chars.size());
		wstream.str(std::basic_string<wchar_t>());
	}
}
LocaleImpl;

String StringBuilder::Build() const
{
	return String(buffer.begin(), buffer.end());
}

void StringBuilder::AddChars(String::value_type const *data, size_t count)
{
	buffer.reserve(buffer.size() + count);
	buffer.insert(buffer.end(), data, data + count);
}

StringBuilder &operator<<(StringBuilder &b, short int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, long int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, long long int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, unsigned short int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, unsigned int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, unsigned long int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, unsigned long long int data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, ByteString::value_type data)
{
	String::value_type ch = data;
	b.AddChars(&ch, 1);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, String::value_type data)
{
	b.AddChars(&data, 1);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, String const &data)
{
	b.AddChars(data.data(), data.size());
	return b;
}

StringBuilder &operator<<(StringBuilder &b, float data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}

StringBuilder &operator<<(StringBuilder &b, double data)
{
	LocaleImpl.PrepareWStream(b);
	LocaleImpl.wstream << data;
	LocaleImpl.FlushWStream(b);
	return b;
}


template<> std::ctype<char32_t>::~ctype()
{
}
template<> std::numpunct<char32_t>::numpunct(size_t ref): std::locale::facet(ref)
{
}
template<> std::numpunct<char32_t>::~numpunct()
{
}

static struct Locale32Impl
{
	std::ctype<wchar_t> const &ctype16;
	std::numpunct<wchar_t> const &numpunct16;
	Locale32Impl():
		ctype16(std::use_facet<std::ctype<wchar_t> >(std::locale())),
		numpunct16(std::use_facet<std::numpunct<wchar_t> >(std::locale()))
	{
		std::locale::global(std::locale(std::locale(), new std::ctype<char32_t>()));
		std::locale::global(std::locale(std::locale(), new std::numpunct<char32_t>()));
		std::locale::global(std::locale(std::locale(), new std::num_put<char32_t>()));
	}
}
Locale32Impl;

template<> bool std::ctype<char32_t>::do_is(mask m, char32_t ch) const
{
	return ch <= 0xFFFF ? Locale32Impl.ctype16.is(m, ch) : (m & print);
}
template<> char32_t const *std::ctype<char32_t>::do_is(char32_t const *low, char32_t const *high, mask *vec) const
{
	while(low < high)
	{
		if(*low <= 0xFFFF)
		{
			wchar_t l = *low;
			Locale32Impl.ctype16.is(&l, &l + 1, vec);
		}
		else
			*vec = print;
		low++;
	}
	return high;
}
template<> char32_t const *std::ctype<char32_t>::do_scan_is(mask m, char32_t const *beg, char32_t const *end) const
{
	while(beg < end)
		if(do_is(m, *beg))
			return beg;
		else
			beg++;
	return end;
}
template<> char32_t const *std::ctype<char32_t>::do_scan_not(mask m, char32_t const *beg, char32_t const *end) const
{
	while(beg < end)
		if(!do_is(m, *beg))
			return beg;
		else
			beg++;
	return end;
}
template<> char32_t std::ctype<char32_t>::do_toupper(char32_t ch) const
{
	return ch <= 0xFFFF ? Locale32Impl.ctype16.toupper(ch) : ch;
}
template<> char32_t const *std::ctype<char32_t>::do_toupper(char32_t *beg, char32_t const *end) const
{
	while(beg < end)
	{
		*beg = do_toupper(*beg);
		beg++;
	}
	return end;
}
template<> char32_t std::ctype<char32_t>::do_tolower(char32_t ch) const
{
	return ch <= 0xFFFF ? Locale32Impl.ctype16.tolower(ch) : ch;
}
template<> char32_t const *std::ctype<char32_t>::do_tolower(char32_t *beg, char32_t const *end) const
{
	while(beg < end)
	{
		*beg = do_tolower(*beg);
		beg++;
	}
	return end;
}
template<> char32_t std::ctype<char32_t>::do_widen(char ch) const
{
	return Locale32Impl.ctype16.widen(ch);
}
template<> char const *std::ctype<char32_t>::do_widen(char const *beg, char const *end, char32_t *dst) const
{
	while(beg < end)
		*(dst++) = do_widen(*(beg++));
	return end;
}
template<> char std::ctype<char32_t>::do_narrow(char32_t ch, char dflt) const
{
	return ch <= 0xFFFF ? Locale32Impl.ctype16.narrow(ch, dflt) : dflt;
}
template<> char32_t const *std::ctype<char32_t>::do_narrow(char32_t const *beg, char32_t const *end, char dflt, char *dst) const
{
	while(beg < end)
		*(dst++) = do_narrow(*(beg++), dflt);
	return end;
}

template<> char32_t std::numpunct<char32_t>::do_decimal_point() const
{
	return Locale32Impl.numpunct16.decimal_point();
}
template<> char32_t std::numpunct<char32_t>::do_thousands_sep() const
{
	return Locale32Impl.numpunct16.thousands_sep();
}
template<> std::string std::numpunct<char32_t>::do_grouping() const
{
	return Locale32Impl.numpunct16.grouping();
}
template<> std::basic_string<char32_t> std::numpunct<char32_t>::do_truename() const
{
	std::basic_string<wchar_t> name = Locale32Impl.numpunct16.truename();
	return std::basic_string<char32_t>(name.begin(), name.end());
}
template<> std::basic_string<char32_t> std::numpunct<char32_t>::do_falsename() const
{
	std::basic_string<wchar_t> name = Locale32Impl.numpunct16.falsename();
	return std::basic_string<char32_t>(name.begin(), name.end());
}