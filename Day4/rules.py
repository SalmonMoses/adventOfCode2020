import re

hcl_pattern = re.compile("^#[0-9a-f]{6}$")
pid_pattern = re.compile("^[0-9]{9}$")


def birth_year(byr):
    return 1920 <= int(byr) <= 2002


def issue_year(iyr):
    return 2010 <= int(iyr) <= 2020


def expiration_year(eyr):
    return 2020 <= int(eyr) <= 2030


def height(hgt):
    unit = hgt[-2:]
    if unit == 'cm':
        return 150 <= int(hgt[0:-2]) <= 193
    elif unit == 'in':
        return 59 <= int(hgt[0:-2]) <= 76
    else:
        return False


def hair_color(hcl):
    return re.match(hcl_pattern, hcl) is not None


def eye_color(ecl):
    return ecl in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']


def passport_id(pid):
    return re.match(pid_pattern, pid) is not None
