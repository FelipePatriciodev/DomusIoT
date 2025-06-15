"use client";

import { useEffect } from "react";
import { useRouter } from "next/navigation";
import LogoutButton from "@/components/LogoutButton";

export default function Dashboard() {
  const router = useRouter();

  useEffect(() => {
    const token = localStorage.getItem("token");

    if (!token) {
      router.push("/login");
      return;
    }

    const validate = async () => {
      try {
        const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/auth/validate`, {
          headers: {
            Authorization: `Bearer ${token}`,
          },
        });

        if (!res.ok) {
          router.push("/login");
        }
      } catch {
        router.push("/login");
      }
    };

    validate();
  }, [router]);

  return (
    <div>
      <header
        className="text-white flex items-center justify-between p-2 px-20"
        style={{ backgroundColor: "#004AAD" }}
      >
        <div>
          <h1 className="text-2xl font-bold">DomusIoT</h1>
          <h2 className="text-lg">Dashboard</h2>
        </div>
        <div className="flex items-center space-x-2">
          <p>User</p>
          <div className="w-10 h-10 rounded-full bg-white text-[#004AAD] flex items-center justify-center">
            <svg
              className="w-5 h-5"
              fill="currentColor"
              viewBox="0 0 24 24"
            >
              <path d="M12 12c2.7 0 5-2.3 5-5s-2.3-5-5-5-5 2.3-5 5 2.3 5 5 5zm0 2c-3.3 0-10 1.7-10 5v3h20v-3c0-3.3-6.7-5-10-5z" />
            </svg>
          </div>
          <LogoutButton />
        </div>
      </header>
      <div className="min-h-screen bg-gray-100 flex items-center justify-center p-10">
        <div className="grid grid-cols-3 gap-6">
          {Array.from({ length: 9 }).map((_, i) => (
            <div
              key={i}
              className="w-40 h-24 bg-blue-500 rounded-lg shadow-md hover:bg-blue-600 transition"
            >
              <p className="text-white text-center pt-8">Box {i + 1}</p>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}