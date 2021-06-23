project(send_mail CXX)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(send_mail ${src} ${hdr})
add_executable(mapi mapi.cxx)
