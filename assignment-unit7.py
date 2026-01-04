def invert_enrollment(student_courses):
    """
    Inverts a dictionary mapping Students -> List of Courses
    to a dictionary mapping Courses -> List of Students.
    """
    # 1. Allocation: Initialize empty hash map (dict) for the result
    course_roster = {}

    # 2. Outer Loop: Iterate through the existing hash map entries
    # .items() returns an iterator of (key, value) tuples
    for student, courses in student_courses.items():

        # 3. Inner Loop: Iterate through the dynamic array (list) of courses
        for course in courses:

            # 4. Hash Lookup & Insertion
            # Check if the course string hash exists in the new dictionary
            if course not in course_roster:
                # Cache Miss: Allocate a new list with the current student
                course_roster[course] = [student]
            else:
                # Cache Hit: Retrieve reference to existing list and append
                course_roster[course].append(student)

    return course_roster

# --- Main Driver Code ---

# Definition of the input graph (Adjacency List style)
original_data = {
    'Stud1': ['CS1101', 'CS2402', 'CS2001'],
    'Stud2': ['CS2402', 'CS2001', 'CS1102']
}

# Execution
inverted_data = invert_enrollment(original_data)

# Output Generation
print("Original Dictionary:")
print(original_data)

print("\nInverted Dictionary:")
# Iterating to print cleanly
for course, students in inverted_data.items():
    print(f"'{course}': {students}")