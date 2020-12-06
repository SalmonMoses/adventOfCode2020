import string
from typing import AnyStr


def process_group_any_answered(group: AnyStr) -> int:
    true_questions = set()
    for person_answers in group.split('\n'):
        for question in person_answers:
            true_questions.add(question)
    return len(true_questions)

def process_group_all_answered(group: AnyStr) -> int:
    all_answered = set(string.ascii_lowercase)
    for person_answers in group.split('\n'):
        person_answered = set()
        for question in person_answers.strip():
            person_answered.add(question)
        all_answered = all_answered & person_answered
    return len(all_answered)


def task_one() -> int:
    questions_answered_true_sum = 0
    with open('data/input.txt') as f:
        cur_group = ''
        for line in f:
            if len(line) == 0 or line.isspace():
                questions_answered_true_sum += process_group_any_answered(cur_group)
                cur_group = ''
                continue
            cur_group += line
        questions_answered_true_sum += process_group_any_answered(cur_group)
    return questions_answered_true_sum

def task_two() -> int:
    questions_answered_true_sum = 0
    with open('data/input.txt') as f:
        cur_group = ''
        for line in f:
            if len(line) == 0 or line.isspace():
                questions_answered_true_sum += process_group_all_answered(cur_group.strip())
                cur_group = ''
                continue
            cur_group += line
        questions_answered_true_sum += process_group_all_answered(cur_group)
    return questions_answered_true_sum


if __name__ == '__main__':
    print(task_two())
