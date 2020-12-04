import re

import rules

passport_entry_pattern = re.compile("[a-zA-Z]{3}:[#a-zA-Z0-9]*")
required_entries = {'byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid', 'cid'}

entries_rules = {
    'byr': rules.birth_year,
    'iyr': rules.issue_year,
    'eyr': rules.expiration_year,
    'hgt': rules.height,
    'hcl': rules.hair_color,
    'ecl': rules.eye_color,
    'pid': rules.passport_id
}


def validate_passport_entries(passport):
    found_entries = {'cid'}
    for entry in re.findall(passport_entry_pattern, passport):
        entry_name = entry.split(':')[0]
        found_entries.add(entry_name)
    return found_entries == required_entries


def validate_passport(passport):
    found_entries = {'cid'}
    for entry in re.findall(passport_entry_pattern, passport):
        entry_name = entry.split(':')[0]
        entry_value = entry.split(':')[1]
        found_entries.add(entry_name)
        if entry_name != 'cid' and not entries_rules[entry_name](entry_value):
            return False
    return found_entries == required_entries


def task_one():
    valid_passports = 0
    with open('data/input.txt') as f:
        cur_passport = ''
        for line in f:
            if len(line) == 0 or line.isspace():
                if validate_passport_entries(cur_passport):
                    valid_passports += 1
                cur_passport = ''
                continue
            cur_passport += line
        if validate_passport_entries(cur_passport):
            valid_passports += 1
    return valid_passports


def task_two():
    valid_passports = 0
    with open('data/input.txt') as f:
        cur_passport = ''
        for line in f:
            if len(line) == 0 or line.isspace():
                if validate_passport(cur_passport):
                    valid_passports += 1
                cur_passport = ''
                continue
            cur_passport += line
        if validate_passport(cur_passport):
            valid_passports += 1
    return valid_passports


if __name__ == '__main__':
    print(task_two())
