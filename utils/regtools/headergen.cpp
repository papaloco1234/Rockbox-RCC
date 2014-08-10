/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2013 by Amaury Pouly
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/ 
#include "soc_desc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>

#define HEADERGEN_VERSION   "2.1.8"

#define error(...) do{ fprintf(stderr, __VA_ARGS__); exit(1); } while(0)

bool g_gen_selector = false;

std::string g_macro_filename;

std::string g_soc_name;
std::string g_soc_dev;
std::string g_soc_reg;
std::string g_soc_field;
std::string g_soc_dev_regs_base;

namespace {
std::string tolower(const std::string s)
{
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

std::string toupper(const std::string& s)
{
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res;
}
}

template< typename T >
std::string to_str(const T& v)
{
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

template< typename T >
std::string to_hex(const T& v)
{
    std::ostringstream oss;
    oss << std::hex << v;
    return oss.str();
}

typedef std::pair< std::string, std::string > xml_ver_t;

void fprint_copyright(FILE *f, const std::vector< xml_ver_t >& versions)
{
    std::ostringstream ver;
    for(size_t i = 0; i < versions.size(); i++)
        ver << " " << versions[i].first << ":" << versions[i].second;

    fprintf(f,"\
/***************************************************************************\n\
 *             __________               __   ___.\n\
 *   Open      \\______   \\ ____   ____ |  | _\\_ |__   _______  ___\n\
 *   Source     |       _//  _ \\_/ ___\\|  |/ /| __ \\ /  _ \\  \\/  /\n\
 *   Jukebox    |    |   (  <_> )  \\___|    < | \\_\\ (  <_> > <  <\n\
 *   Firmware   |____|_  /\\____/ \\___  >__|_ \\|___  /\\____/__/\\_ \\\n\
 *                     \\/            \\/     \\/    \\/            \\/\n\
 * This file was automatically generated by headergen, DO NOT EDIT it.\n\
 * headergen version: " HEADERGEN_VERSION "\n");
    if(versions.size() > 0)
        fprintf(f, " * XML versions:%s\n", ver.str().c_str());
    fprintf(f,"\
 *\n\
 * Copyright (C) 2013 by Amaury Pouly\n\
 *\n\
 * This program is free software; you can redistribute it and/or\n\
 * modify it under the terms of the GNU General Public License\n\
 * as published by the Free Software Foundation; either version 2\n\
 * of the License, or (at your option) any later version.\n\
 *\n\
 * This software is distributed on an \"AS IS\" basis, WITHOUT WARRANTY OF ANY\n\
 * KIND, either express or implied.\n\
 *\n\
 ****************************************************************************/\n");
}

void fprint_copyright(FILE *f, const xml_ver_t& version)
{
    fprint_copyright(f, std::vector< xml_ver_t >(1, version));
}

void fprint_copyright(FILE *f)
{
    fprint_copyright(f, std::vector< xml_ver_t >());
}

void fprint_include_guard_ex(FILE *f, bool begin, const std::string& name)
{
    if(begin)
    {
        fprintf(f, "#ifndef %s\n", name.c_str());
        fprintf(f, "#define %s\n", name.c_str());
    }
    else
        fprintf(f, "#endif /* %s */\n", name.c_str());
}

void fprint_include_guard(FILE *f, bool begin)
{
    std::string name = "__HEADERGEN__" + toupper(g_soc_name) + "__" + toupper(g_soc_dev)
        + "__H__";
    fprint_include_guard_ex(f, begin, name);
}

struct limited_column_context_t
{
    limited_column_context_t(size_t nr_col = 80)
        :m_nr_col(nr_col), m_prevent_wordcut(true) {}
    void set_prefix(const std::string& prefix) { m_prefix = prefix; }
    void add(const std::string& text)
    {
        for(size_t i = 0; i < text.size();)
        {
            size_t offset = 0;
            if(m_cur_line.size() == 0)
                m_cur_line = m_prefix;
            size_t len = std::min(text.size() - i, m_nr_col - m_cur_line.size());
            // prevent word cut
            if(m_prevent_wordcut && !isspace(text[i + len - 1]) && 
                    i + len < text.size() && !isspace(text[i + len]))
            {
                size_t pos = text.find_last_of(" \t\n\v\r\f", i + len - 1);
                if(pos == std::string::npos || pos < i)
                    len = 0;
                else
                    len = pos - i + 1;
            }
            size_t pos = text.find('\n', i);
            if(pos != std::string::npos && pos <= i + len)
            {
                offset = 1;
                len = pos - i;
            }
            m_cur_line += text.substr(i, len);
            // len == 0 means we need a new line
            if(m_cur_line.size() == m_nr_col || len == 0)
            {
                m_lines.push_back(m_cur_line);
                m_cur_line = "";
            }
            i += len + offset;
        }
    }

    std::string to_string()
    {
        std::string str;
        for(size_t i = 0; i < m_lines.size(); i++)
            str += m_lines[i] + "\n";
        if(m_cur_line.size() != 0)
            str += m_cur_line + "\n";
        return str;
    }

    void print(FILE *f)
    {
        fprintf(f, "%s", to_string().c_str());
    }

    std::vector< std::string > m_lines;
    std::string m_cur_line;
    std::string m_prefix;
    size_t m_nr_col;
    bool m_prevent_wordcut;
};

struct define_align_context_t
{
    define_align_context_t():m_max_name(0) {}
    void add(const std::string& name, const std::string& val)
    {
        m_lines.push_back(std::make_pair(name, val));
        m_max_name = std::max(m_max_name, name.size());
    }

    void add_raw(const std::string& line)
    {
        m_lines.push_back(std::make_pair("", line));
    }

    void print(FILE *f)
    {
        std::string define = "#define ";
        size_t align = define.size() + m_max_name + 1;
        align = ((align + 3) / 4) * 4;

        for(size_t i = 0; i < m_lines.size(); i++)
        {
            std::string name = m_lines[i].first;
            // raw entry ?
            if(name.size() == 0)
            {
                fprintf(f, "%s", m_lines[i].second.c_str());
                continue;
            }
            name.insert(name.end(), align - define.size() - name.size(), ' ');
            fprintf(f, "%s%s%s\n", define.c_str(), name.c_str(), m_lines[i].second.c_str());
        }
    }

    size_t m_max_name;
    std::vector< std::pair< std::string, std::string > > m_lines;
};

limited_column_context_t print_description(const std::string& desc, const std::string& prefix)
{
    limited_column_context_t ctx;
    if(desc.size() == 0)
        return ctx;
    ctx.set_prefix(prefix);
    ctx.add(desc);
    return ctx;
}

void fprint_description(FILE *f, const std::string& desc, const std::string& prefix)
{
    limited_column_context_t ctx = print_description(desc, prefix);
    ctx.print(f);
}

void fprint_description(define_align_context_t& ctx, const std::string& desc, const std::string& prefix)
{
    limited_column_context_t ctx2 = print_description(desc, prefix);
    ctx.add_raw(ctx2.to_string());
}

void gen_soc_field(define_align_context_t& ctx, bool multidev, bool multireg, const soc_reg_field_t& field)
{
    if(field.desc.size() != 0)
    {
        ctx.add_raw("/* Field: " + field.name + "\n");
        fprint_description(ctx, "Description: " + field.desc + " */\n", " * ");
    }

    std::string prefix = g_soc_dev + "_" + g_soc_reg + "_" + g_soc_field;
    ctx.add("BP_" + prefix, to_str(field.first_bit));
    ctx.add("BM_" + prefix, "0x" + to_hex(field.bitmask()));

    for(size_t i = 0; i < field.value.size(); i++)
        ctx.add("BV_" + prefix + "__" + field.value[i].name, "0x" + to_hex(field.value[i].value));

    ctx.add("BF_" + prefix + "(v)", "(((v) << " + to_str(field.first_bit) + ") & 0x" + to_hex(field.bitmask()) + ")");

    if(field.value.size() > 0)
        ctx.add("BF_" + prefix + "_V(v)", "((BV_" + prefix + "__##v" + " << " + to_str(field.first_bit) + ") & 0x" + to_hex(field.bitmask()) + ")");
}

void gen_soc_reg(FILE *f, bool multidev, const soc_reg_t& reg)
{
    bool multireg = reg.addr.size() > 1;

    static const char *suffix[] = {"", "_SET", "_CLR", "_TOG"};
    bool sct = !!(reg.flags & REG_HAS_SCT);

    fprintf(f, "/**\n");
    fprintf(f, " * Register: HW_%s_%s\n", g_soc_dev.c_str(), g_soc_reg.c_str());
    fprintf(f, " * Address:");
    if(multireg && reg.formula.type == REG_FORMULA_STRING)
    {
        fprintf(f, " %s\n", reg.formula.string.c_str());
    }
    else
    {
        for(size_t i = 0; i < reg.addr.size(); i++)
            fprintf(f, " %#x", reg.addr[i].addr);
        fprintf(f, "\n");
    }
    fprintf(f, " * SCT: %s\n", sct ? "yes" : "no");
    if(reg.desc.size() != 0)
        fprint_description(f, "Description: " + reg.desc, " * ");
    fprintf(f, " */\n");

    define_align_context_t ctx;

    for(int i = 0; i < (sct ? 4 : 1); i++)
    {
        std::ostringstream name;
        name << "HW_" << g_soc_dev << "_" << g_soc_reg << suffix[i];
        if(multidev || multireg)
        {
            name << "(";
            if(multidev)
                name << "d";
            if(multidev && multireg)
                name << ",";
            if(multireg)
                name << "n";
            name << ")";
        }
        std::ostringstream value;
        value << "(*(volatile unsigned long *)(" << g_soc_dev_regs_base;
        if(multidev)
            value << "(d)";
        value << " + ";
        if(multireg)
        {
            if(reg.formula.type != REG_FORMULA_STRING)
                printf("Warning: register HW_%s_%s has no formula !\n", g_soc_dev.c_str(), g_soc_reg.c_str());
            std::string formula = reg.formula.string.c_str();
            size_t pos = formula.find("n");
            while(pos != std::string::npos)
            {
                formula.replace(pos, 1, "(n)");
                pos = formula.find("n", pos + 2);
            }
            value << formula;
        }
        else
            value << "0x" << std::hex << reg.addr[0].addr;

        if(sct)
            value << " + 0x" << std::hex << (i * 4);
        value << "))";

        ctx.add(name.str(), value.str());
    }

    for(size_t i = 0; i < reg.field.size(); i++)
    {
        g_soc_field = reg.field[i].name;
        gen_soc_field(ctx, multidev, multireg, reg.field[i]);
    }

    ctx.print(f);

    fprintf(f, "\n");
}

void gen_soc_dev_header(const std::string& filename, const xml_ver_t& ver, const soc_dev_t& dev)
{
    /*
    printf("Generate headers for soc %s, dev %s: use file %s\n", g_soc_name.c_str(),
        g_soc_dev.c_str(), filename.c_str());
    */
    FILE *f = fopen(filename.c_str(), "w");
    if(f == NULL)
    {
        printf("Cannot open %s for writing: %m\n", filename.c_str());
        return;
    }
    fprint_copyright(f, ver);
    fprint_include_guard(f, true);
    if(g_macro_filename.size() > 0)
        fprintf(f, "#include \"%s\"\n", g_macro_filename.c_str());

    /* print base */
    fprintf(f, "\n");
    g_soc_dev_regs_base = "REGS_" + g_soc_dev + "_BASE";
    fprintf(f, "#define %s", g_soc_dev_regs_base.c_str());

    if(dev.addr.size() > 1)
        fprintf(f, "(i)");
    fprintf(f, " (");
    
    for(size_t i = 0; i < dev.addr.size() - 1; i++)
        fprintf(f, "(i) == %d ? %#x : ", (int)i + 1, dev.addr[i].addr);
    
    fprintf(f, "%#x)\n", dev.addr[dev.addr.size() - 1].addr);

    fprintf(f, "\n");

    /* print version */
    fprintf(f, "#define REGS_%s_VERSION \"%s\"\n\n", g_soc_dev.c_str(), dev.version.c_str());

    for(size_t i = 0; i < dev.reg.size(); i++)
    {
        g_soc_reg = dev.reg[i].name;
        gen_soc_reg(f, dev.addr.size() > 1, dev.reg[i]);
    }

    fprint_include_guard(f, false);
    fclose(f);
}

void gen_soc_headers(const std::string& prefix, const soc_t& soc)
{
    printf("Generate headers for soc %s: use directory %s\n", soc.name.c_str(),
        prefix.c_str());
    mkdir(prefix.c_str(), 0770);

    for(size_t i = 0; i < soc.dev.size(); i++)
    {
        g_soc_dev = soc.dev[i].name;
        xml_ver_t ver(soc.name, soc.dev[i].version);
        gen_soc_dev_header(prefix + "/regs-" + tolower(g_soc_dev.c_str()) + ".h", ver, soc.dev[i]);
    }
}

void gen_headers(const std::string& prefix, const std::vector< soc_t >& socs)
{
    for(size_t i = 0; i < socs.size(); i++)
    {
        g_soc_name = socs[i].name;
        std::string dir = prefix;
        if(g_gen_selector)
            dir += "/" + socs[i].name;
        gen_soc_headers(dir, socs[i]);
    }
}

typedef std::map< std::string, std::vector< std::pair< size_t, size_t > > > general_dev_list_t;
general_dev_list_t build_general_dev_list(const std::vector< soc_t >& socs)
{
    general_dev_list_t map;
    for(size_t i = 0; i < socs.size(); i++)
    {
        for(size_t j = 0; j < socs[i].dev.size(); j++)
            map[tolower(socs[i].dev[j].name)].push_back(std::make_pair(i,j));
    }
    return map;
}

void gen_select_header(const std::string& filename, const std::string& dev,
    const std::vector< std::string >& socs, const std::vector< xml_ver_t >& ver)
{
    std::string guard = "__SELECT__" + toupper(dev) + "__H__";
    FILE *f = fopen(filename.c_str(), "w");
    if(f == NULL)
        error("Cannot open file %s\n", filename.c_str());
    fprint_copyright(f, ver);
    fprint_include_guard_ex(f, true, guard);
    if(g_macro_filename.size() > 0)
        fprintf(f, "#include \"%s\"\n", g_macro_filename.c_str());
    fprintf(f, "\n");

    for(size_t i = 0; i < socs.size(); i++)
    {
        fprintf(f, "#define %s_INCLUDE \"%s/regs-%s.h\"\n",
            toupper(socs[i]).c_str(), tolower(socs[i]).c_str(),
            tolower(dev).c_str());
    }
    fprintf(f, "\n#include \"regs-select.h\"\n\n");
    for(size_t i = 0; i < socs.size(); i++)
    {
        fprintf(f, "#undef %s_INCLUDE\n", toupper(socs[i]).c_str());
    }
    fprintf(f, "\n");
    fprint_include_guard_ex(f, false, guard);
    fclose(f);
}

void gen_selectors(const std::string& prefix, const std::vector< soc_t >& socs)
{
    printf("Generate select headers: use directory %s\n",  prefix.c_str());
    general_dev_list_t map = build_general_dev_list(socs);
    for(general_dev_list_t::iterator it = map.begin(); it != map.end(); ++it)
    {
        std::vector< xml_ver_t > ver;
        std::vector< std::string > names;
        for(size_t i = 0; i < it->second.size(); i++)
        {
            size_t soc_nr = it->second[i].first;
            size_t dev_in_soc_nr = it->second[i].second;
            ver.push_back(std::make_pair(socs[soc_nr].name, socs[soc_nr].dev[dev_in_soc_nr].version));
            names.push_back(socs[soc_nr].name);
        }
        gen_select_header(prefix + "/regs-" + it->first + ".h", it->first, names, ver);
    }
}

void gen_macro_list(FILE *f, const std::string& prefix, int count, int nr_digits,
    const std::string& sep, int max_per_line = 1000, const std::string& align = "")
{
    for(int i = 1; i <= count;)
    {
        for(int j = i; j <= std::min(count, i + max_per_line - 1); j++)
        {
            fprintf(f, "%s%0*d", prefix.c_str(), nr_digits, j);
            if(j < count)
                fprintf(f, "%s", sep.c_str());
        }
        i += max_per_line;
        if(i <= count)
            fprintf(f, "\\\n%s", align.c_str());
    }
}

void gen_macro(const std::string& filename, bool variadic)
{
    printf("Generate %smacro header: use %s\n", variadic ? "": "non-variadic ",
        filename.c_str());
    std::string guard = "__REGS__MACRO__H__";
    FILE *f = fopen(filename.c_str(), "w");
    if(f == NULL)
        error("Cannot open file %s\n", filename.c_str());
    fprint_copyright(f);
    fprint_include_guard_ex(f, true, guard);
    fprintf(f, "\n");

#define REG_WRITE "REG_WRITE"
    fprintf(f, "#ifndef %s\n", REG_WRITE);
    fprintf(f, "#define %s(var,value) ((var) = (value))\n", REG_WRITE);
    fprintf(f, "#endif /* %s */\n", REG_WRITE);
    fprintf(f, "\n");

#define REG_READ "REG_READ"
    fprintf(f, "#ifndef %s\n", REG_READ);
    fprintf(f, "#define %s(var) (var)\n", REG_READ);
    fprintf(f, "#endif /* %s */\n", REG_READ);
    fprintf(f, "\n");

    const int MAX_NARGS = 32;

    fprintf(f, "\
#define BF_SET(reg, field)              "REG_WRITE"(HW_##reg##_SET, BM_##reg##_##field)\n\
#define BF_CLR(reg, field)              "REG_WRITE"(HW_##reg##_CLR, BM_##reg##_##field)\n\
#define BF_TOG(reg, field)              "REG_WRITE"(HW_##reg##_TOG, BM_##reg##_##field)\n\
\n\
#define BF_SETV(reg, field, v)          "REG_WRITE"(HW_##reg##_SET, BF_##reg##_##field(v))\n\
#define BF_CLRV(reg, field, v)          "REG_WRITE"(HW_##reg##_CLR, BF_##reg##_##field(v))\n\
#define BF_TOGV(reg, field, v)          "REG_WRITE"(HW_##reg##_TOG, BF_##reg##_##field(v))\n\
\n\
#define BF_RDX(val, reg, field)         (("REG_READ"(val) & BM_##reg##_##field) >> BP_##reg##_##field)\n\
#define BF_RD(reg, field)               BF_RDX("REG_READ"(HW_##reg), reg, field)\n\
#define BF_WRX(val, reg, field, v)      "REG_WRITE"(val, ("REG_READ"(val) & ~BM_##reg##_##field) | (((v) << BP_##reg##_##field) & BM_##reg##_##field))\n\
#define BF_WR(reg, field, v)            BF_WRX(HW_##reg, reg, field, v)\n\
#define BF_WR_V(reg, field, sy)         BF_WR(reg, field, BV_##reg##_##field##__##sy)\n\
#define BF_WR_VX(val, reg, field, sy)   BF_WRX(val, reg, field, BV_##reg##_##field##__##sy)\n\
\n\
#define BF_SETn(reg, n, field)          "REG_WRITE"(HW_##reg##_SET(n), BM_##reg##_##field)\n\
#define BF_CLRn(reg, n, field)          "REG_WRITE"(HW_##reg##_CLR(n), BM_##reg##_##field)\n\
#define BF_TOGn(reg, n, field)          "REG_WRITE"(HW_##reg##_TOG(n), BM_##reg##_##field)\n\
\n\
#define BF_SETVn(reg, n, field, v)      "REG_WRITE"(HW_##reg##_SET(n), BF_##reg##_##field(v))\n\
#define BF_CLRVn(reg, n, field, v)      "REG_WRITE"(HW_##reg##_CLR(n), BF_##reg##_##field(v))\n\
#define BF_TOGVn(reg, n, field, v)      "REG_WRITE"(HW_##reg##_TOG(n), BF_##reg##_##field(v))\n\
\n\
#define BF_RDn(reg, n, field)           BF_RDX(HW_##reg(n), reg, field)\n\
#define BF_WRn(reg, n, field, v)        BF_WRX(HW_##reg(n), reg, field, v)\n\
#define BF_WRn_V(reg, n, field, sy)     BF_WRn(reg, n, field, BV_##reg##_##field##__##sy)\n\
\n");

    for(int nargs = 1; nargs <= MAX_NARGS; nargs++)
    {
        fprintf(f, "#define BM_OR%d(reg, ", nargs);
        gen_macro_list(f, "f", nargs, 2, ", ", 10, "        ");
        fprintf(f, ") \\\n    (");
        gen_macro_list(f, "BM_##reg##_##f", nargs, 2, " | ", 4, "     ");
        fprintf(f, ")\n");
    }
    fprintf(f, "\n");

    for(int nargs = 1; nargs <= MAX_NARGS; nargs++)
    {
        fprintf(f, "#define BF_OR%d(reg, ", nargs);
        gen_macro_list(f, "f", nargs, 2, ", ", 10, "        ");
        fprintf(f, ") \\\n    (");
        gen_macro_list(f, "BF_##reg##_##f", nargs, 2, " | ", 4, "     ");
        fprintf(f, ")\n");
    }
    fprintf(f, "\n");

    if(variadic)
    {
        fprintf(f, "#define REG_NARG(...) REG_NARGS_(__VA_ARGS__");
        for(int i = MAX_NARGS; i >= 1; i--)
            fprintf(f, ", %d", i);
        fprintf(f, ")\n");
        fprintf(f, "#define REG_NARGS_(");
        gen_macro_list(f, "_", MAX_NARGS, 1, ", ");
        fprintf(f, ", N, ...) N\n\n");

        fprintf(f, "#define REG_VARIADIC(macro, reg, ...) REG_VARIADIC_(macro, REG_NARG(__VA_ARGS__), reg, __VA_ARGS__)\n");
        fprintf(f, "#define REG_VARIADIC_(macro, cnt, reg, ...) REG_VARIADIC__(macro, cnt, reg, __VA_ARGS__)\n");
        fprintf(f, "#define REG_VARIADIC__(macro, cnt, reg, ...) REG_VARIADIC___(macro##cnt, reg, __VA_ARGS__)\n");
        fprintf(f, "#define REG_VARIADIC___(macro, reg, ...) macro(reg, __VA_ARGS__)\n\n");

        fprintf(f, "#define BM_OR(reg, ...) REG_VARIADIC(BM_OR, reg, __VA_ARGS__)\n");
        fprintf(f, "#define BF_OR(reg, ...) REG_VARIADIC(BF_OR, reg, __VA_ARGS__)\n");
    }

    fprint_include_guard_ex(f, false, guard);
    fclose(f);
}

void usage()
{
    printf("usage: headergen [options] <desc files...> <output directory>\n");
    printf("options:\n");
    printf("  -?/--help         Dispaly this help\n");
    printf("  -s/--selector     Always produce selector files\n");
    printf("  -m/--no-macro     Do not generate a macro file with helpers\n");
    printf("  -i/--no-include   Do not include the macro file in the headers\n");
    printf("  -v/--no-variadic  Do not generate variadic macros\n");
    printf("Default option is to generate a macro file with variadic macros.\n");
    printf("Default option is to include the macro file in the headers.\n");
    printf("Default option is to generate selector files only for two or more socs.\n");
    printf("Default option is to create one subdirectory per soc, except if no\n");
    printf("selector files are needed. The subdirectories will be created if\n");
    printf("necessary.\n");
    exit(1);
}

int main(int argc, char **argv)
{
    bool force_selector = false;
    bool no_variadic = false;
    bool no_macro = false;
    bool no_include = false;
    if(argc <= 1)
        usage();

    while(1)
    {
        static struct option long_options[] =
        {
            {"help", no_argument, 0, '?'},
            {"selector", no_argument, 0, 's'},
            {"no-macro", no_argument, 0, 'm'},
            {"no-include", no_argument, 0, 'i'},
            {"no-variadic", no_argument, 0, 'v'},
            {0, 0, 0, 0}
        };

        int c = getopt_long(argc, argv, "?smiv", long_options, NULL);
        if(c == -1)
            break;
        switch(c)
        {
            case -1:
                break;
            case '?':
                usage();
                break;
            case 's':
                force_selector = true;
                break;
            case 'm':
                no_macro = true;
                break;
            case 'i':
                no_include = true;
                break;
            case 'v':
                no_variadic = true;
                break;
            default:
                abort();
        }
    }

    std::vector< soc_t > socs;
    for(int i = optind; i < argc - 1; i++)
    {
        soc_t s;
        if(!soc_desc_parse_xml(argv[i], s))
        {
            printf("Cannot parse %s\n", argv[i]);
            return 1;
        }
        socs.push_back(s);
    }

    g_gen_selector = force_selector || socs.size() > 1;

    if(!no_macro)
    {
        g_macro_filename = std::string(argv[argc - 1]) + "/regs-macro.h";
        gen_macro(g_macro_filename, !no_variadic);
        g_macro_filename = "regs-macro.h";
        if(no_include)
           g_macro_filename.clear();
    }
    if(g_gen_selector)
    {
        gen_selectors(argv[argc - 1], socs);
        g_macro_filename.clear();
    }
    gen_headers(argv[argc - 1], socs);
    return 0;
}